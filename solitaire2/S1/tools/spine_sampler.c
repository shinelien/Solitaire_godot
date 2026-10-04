/* Offline sampler using the original, unmodified Cocos project's Spine runtime.
 * Runtime sources and their license remain in reference/InvincibleWarrior-runtime.
 * This executable is not part of the shipped Godot game. */
#include <spine/spine.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void _spAtlasPage_createTexture(spAtlasPage* page, const char* path) {
 FILE *f=fopen(path,"rb"); unsigned char h[24]; if(!f){fprintf(stderr,"Missing atlas page: %s\n",path);exit(2);} fread(h,1,24,f);fclose(f);
 page->width=(h[16]<<24)|(h[17]<<16)|(h[18]<<8)|h[19];page->height=(h[20]<<24)|(h[21]<<16)|(h[22]<<8)|h[23];
}
char* _spUtil_readFile(const char* path,int* length){ FILE* f=fopen(path,"rb"); if(!f)return NULL;fseek(f,0,SEEK_END);*length=(int)ftell(f);rewind(f);char* d=malloc(*length);fread(d,1,*length,f);fclose(f);return d; }
void _spAtlasPage_disposeTexture(spAtlasPage* page){}
static void floats(float* a,int count,int yflip) {printf("[");for(int i=0;i<count;i++)printf("%s%.5f",i?",":"",yflip&&i%2?-a[i]:a[i]);printf("]");}
static void output(spSkeleton* s) {
 printf("[");int first=1;
 for(int i=0;i<s->slotsCount;i++){
  spSlot* slot=s->drawOrder[i];spAttachment* a=slot->attachment;if(!a)continue;
  float vs[4096];float* uv=NULL;unsigned short* indices=NULL;unsigned short ri[]={0,1,2,2,3,0};int cnt=0,ic=0;spColor ac;spAtlasRegion* region=NULL;
  if(a->type==SP_ATTACHMENT_REGION){spRegionAttachment* r=(spRegionAttachment*)a;spRegionAttachment_computeWorldVertices(r,slot->bone,vs,0,2);uv=r->uvs;indices=ri;cnt=8;ic=6;ac=r->color;region=(spAtlasRegion*)r->rendererObject;}
  else if(a->type==SP_ATTACHMENT_MESH){spMeshAttachment* m=(spMeshAttachment*)a;cnt=m->super.worldVerticesLength;if(cnt>4096)exit(3);spVertexAttachment_computeWorldVertices(&m->super,slot,0,cnt,vs,0,2);uv=m->uvs;indices=m->triangles;ic=m->trianglesCount;ac=m->color;region=(spAtlasRegion*)m->rendererObject;}
  else {fprintf(stderr,"Unsupported attachment %d %s\n",a->type,a->name);exit(4);}
  printf("%s{\"slot\":\"%s\",\"name\":\"%s\",\"page\":\"%s\",\"blend\":%d,\"color\":[%.5f,%.5f,%.5f,%.5f],\"vertices\":",first?"":",",slot->data->name,a->name,region->page->name,slot->data->blendMode,slot->color.r*ac.r,slot->color.g*ac.g,slot->color.b*ac.b,slot->color.a*ac.a);first=0;floats(vs,cnt,1);
  printf(",\"uv\":");floats(uv,cnt,0);printf(",\"triangles\":[");for(int j=0;j<ic;j++)printf("%s%d",j?",":"",indices[j]);printf("],\"region\":[%f,%f,%f,%f,%d]}",region->u,region->v,region->u2,region->v2,region->rotate);
 }
 printf("]");
}
int main(int argc,char** argv){
 if(argc<4){fprintf(stderr,"Usage sampler skeleton.json atlas skin [fps]\n");return 1;}
 int fps=argc>4?atoi(argv[4]):60;spAtlas* atlas=spAtlas_createFromFile(argv[2],NULL);spSkeletonJson* json=spSkeletonJson_create(atlas);spSkeletonData* data=spSkeletonJson_readSkeletonDataFile(json,argv[1]);
 if(!data){fprintf(stderr,"%s\n",json->error);return 2;}spSkeleton* s=spSkeleton_create(data);if(strcmp(argv[3],"default"))spSkeleton_setSkinByName(s,argv[3]);
 /* Card replacement regions use full untrimmed PNGs in Godot. Normalize only
 * the three dynamic region slots so their sampled quads include that padding. */
 if(strstr(argv[1],"/pk/skeleton.json"))for(int i=0;i<s->slotsCount;i++){
  spSlot* slot=s->slots[i];if(strncmp(slot->data->name,"poker",5)||!slot->attachment||slot->attachment->type!=SP_ATTACHMENT_REGION)continue;
  spRegionAttachment* r=(spRegionAttachment*)slot->attachment;r->regionOffsetX=0;r->regionOffsetY=0;r->regionWidth=r->regionOriginalWidth;r->regionHeight=r->regionOriginalHeight;spRegionAttachment_updateOffset(r);
 }
 printf("{\"fps\":%d,\"clips\":{",fps);
 for(int ai=-1;ai<data->animationsCount;ai++){
  spAnimation* animation=ai<0?NULL:data->animations[ai];float len=animation?animation->duration:0;int count=animation?(int)ceil(len*fps)+1:1;
  printf("%s\"%s\":{\"duration\":%.5f,\"frames\":[",ai<0?"":",",animation?animation->name:"RESET",len);
  for(int fi=0;fi<count;fi++){
   float t=fminf(len,fi/(float)fps);spSkeleton_setToSetupPose(s);if(animation)spAnimation_apply(animation,s,t,t,0,NULL,NULL,1,SP_MIX_POSE_SETUP,SP_MIX_DIRECTION_IN);spSkeleton_updateWorldTransform(s);
   if(fi)printf(",");output(s);
  }printf("]}");
 }printf("}}\n");spSkeleton_dispose(s);spSkeletonData_dispose(data);spSkeletonJson_dispose(json);spAtlas_dispose(atlas);return 0;
}
