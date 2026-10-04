<GameFile>
  <PropertyGroup Name="banner" Type="Node" ID="c7b2b78f-8bfd-466b-8282-2ecccf54d947" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="25" Speed="1.0000" ActivedAnimationName="start">
        <Timeline ActionTag="1745193476" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.2000" Y="1.2000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.5000" Y="1.5000">
            <EasingData Type="1" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="1.2000" Y="1.2000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="start" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="85" G="107" B="47" />
        </AnimationInfo>
        <AnimationInfo Name="idle" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="255" G="99" B="71" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="266" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image_banner" ActionTag="-942255317" Tag="306" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-540.0000" RightMargin="-540.0000" TopMargin="-322.0000" LeftEage="1" RightEage="1" Scale9OriginX="1" Scale9Width="1" Scale9Height="3" ctype="ImageViewObjectData">
            <Size X="1080.0000" Y="322.0000" />
            <Children>
              <AbstractNodeData Name="Node_LimitScore" Visible="False" ActionTag="-561961759" Tag="3020" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="218.9600" BottomMargin="103.0400" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Node_score" ActionTag="-551941896" Tag="1715" IconVisible="True" TopMargin="25.0000" BottomMargin="-25.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position Y="-25.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="644355674" Tag="3084" IconVisible="False" LeftMargin="86.4998" RightMargin="-253.4998" TopMargin="-66.7600" BottomMargin="62.7600" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="-1092151887" Tag="3085" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="169.9998" Y="64.7600" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerScore" ActionTag="-1135016975" Alpha="102" Tag="3086" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-64.5000" RightMargin="-64.5000" TopMargin="-85.7600" BottomMargin="43.7600" FontSize="36" LabelText="SCORE" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="129.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="64.7600" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="103.0400" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3200" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_CollectPoker" ActionTag="1580127513" Tag="969" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="228.6200" BottomMargin="93.3800" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_3" ActionTag="-1407230148" Tag="1036" IconVisible="False" RightMargin="-314.0000" TopMargin="-54.0000" BottomMargin="-86.0000" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                    <Size X="314.0000" Y="140.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_3_0" ActionTag="-545598664" Tag="3973" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="0.0001" RightMargin="-0.0001" FlipX="True" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                        <Size X="314.0000" Y="140.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="0.0001" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_tips" Visible="False" ActionTag="1109862858" VisibleForFrame="False" Tag="2035" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="215.3928" RightMargin="-1.3928" TopMargin="20.0000" BottomMargin="20.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="100.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="265.3928" Y="70.0000" />
                        <Scale ScaleX="0.8000" ScaleY="0.8000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8452" Y="0.5000" />
                        <PreSize X="0.3185" Y="0.7143" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="level_Collect_btn0.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_1" ActionTag="332546260" Tag="6150" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-58.6238" RightMargin="372.6238" TopMargin="71.5680" BottomMargin="68.4320" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card1" ActionTag="-1805404953" Tag="6151" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card1" ActionTag="-1449291702" VisibleForFrame="False" Tag="7519" IconVisible="False" LeftMargin="-20.0000" RightMargin="-80.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="30.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="-58.6238" Y="68.4320" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-0.1867" Y="0.4888" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_2" ActionTag="-261529688" Tag="6152" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="58.6238" RightMargin="255.3762" TopMargin="71.5680" BottomMargin="68.4320" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card2" ActionTag="1747753841" Tag="6153" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card2" ActionTag="-722197428" VisibleForFrame="False" Tag="7518" IconVisible="False" LeftMargin="-20.0000" RightMargin="-80.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="30.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="58.6238" Y="68.4320" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1867" Y="0.4888" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_3" ActionTag="1921998488" Tag="6148" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-175.8400" RightMargin="489.8400" TopMargin="70.0000" BottomMargin="70.0000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card3" ActionTag="-838756927" Tag="6149" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card3" ActionTag="563926226" VisibleForFrame="False" Tag="7517" IconVisible="False" LeftMargin="-25.0000" RightMargin="-75.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="25.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="-175.8400" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-0.5600" Y="0.5000" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_4" ActionTag="-1438968099" Tag="3979" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="175.8400" RightMargin="138.1600" TopMargin="70.0000" BottomMargin="70.0000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_card4" ActionTag="-1732217455" Tag="5698" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="Text_card4" ActionTag="-1627477438" VisibleForFrame="False" Tag="7516" IconVisible="False" LeftMargin="-25.0000" RightMargin="-75.0000" TopMargin="-5.0000" BottomMargin="-85.0000" LabelText="10" ctype="TextBMFontObjectData">
                            <Size X="100.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="25.0000" Y="-40.0000" />
                            <Scale ScaleX="0.4000" ScaleY="0.4000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position X="175.8400" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5600" Y="0.5000" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position Y="-16.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_6" ActionTag="1070922911" Tag="719" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="1635076975" Tag="1033" IconVisible="False" LeftMargin="86.9375" RightMargin="-253.9375" TopMargin="-76.4200" BottomMargin="72.4200" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="533930698" Tag="1034" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.4375" Y="74.4200" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerCollet" ActionTag="678744633" Alpha="102" Tag="1035" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-83.5000" RightMargin="-83.5000" TopMargin="-95.4200" BottomMargin="53.4200" FontSize="36" LabelText="COLLECT" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="167.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="74.4200" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="93.3800" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2900" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_TargetPoker" Visible="False" ActionTag="-215702111" Tag="419" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="228.6200" BottomMargin="93.3800" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_3" ActionTag="-602499186" Tag="420" IconVisible="False" RightMargin="-283.0000" TopMargin="-54.0000" BottomMargin="-86.0000" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                    <Size X="283.0000" Y="140.0000" />
                    <Children>
                      <AbstractNodeData Name="Image_3_0" ActionTag="232986261" Tag="421" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="0.0001" RightMargin="-0.0001" FlipX="True" Scale9Enable="True" LeftEage="46" RightEage="46" TopEage="59" BottomEage="59" Scale9OriginX="46" Scale9OriginY="59" Scale9Width="191" Scale9Height="40" ctype="ImageViewObjectData">
                        <Size X="283.0000" Y="140.0000" />
                        <AnchorPoint ScaleY="0.5000" />
                        <Position X="0.0001" Y="70.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Button_tips" Visible="False" ActionTag="938924665" VisibleForFrame="False" Tag="422" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="199.0400" RightMargin="-16.0400" TopMargin="20.0000" BottomMargin="20.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="78" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="100.0000" Y="100.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="249.0400" Y="70.0000" />
                        <Scale ScaleX="0.9000" ScaleY="0.9000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.8800" Y="0.5000" />
                        <PreSize X="0.3534" Y="0.7143" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <DisabledFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui.plist" />
                        <PressedFileData Type="PlistSubImage" Path="level_Collect_btn1.png" Plist="ui.plist" />
                        <NormalFileData Type="PlistSubImage" Path="level_Collect_btn0.png" Plist="ui.plist" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Node_Target1" ActionTag="980847240" Tag="423" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="283.0000" TopMargin="71.4000" BottomMargin="68.6000" ctype="SingleNodeObjectData">
                        <Size X="0.0000" Y="0.0000" />
                        <Children>
                          <AbstractNodeData Name="Sprite_cardTarget1" ActionTag="-2111448796" Tag="424" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                            <Size X="46.0000" Y="46.0000" />
                            <Children>
                              <AbstractNodeData Name="Text_cardTarget1" ActionTag="1012941108" Tag="425" IconVisible="False" LeftMargin="38.0696" RightMargin="-88.0696" TopMargin="-27.9872" BottomMargin="-16.0128" LabelText="12" ctype="TextBMFontObjectData">
                                <Size X="96.0000" Y="90.0000" />
                                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                                <Position X="86.0696" Y="28.9872" />
                                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                                <CColor A="255" R="255" G="255" B="255" />
                                <PrePosition X="1.8711" Y="0.6302" />
                                <PreSize X="2.0870" Y="1.9565" />
                                <LabelBMFontFile_CNB Type="Normal" Path="font/level_num22x.fnt" Plist="" />
                              </AbstractNodeData>
                            </Children>
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position />
                            <Scale ScaleX="1.0000" ScaleY="1.0000" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition />
                            <PreSize X="0.0000" Y="0.0000" />
                            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                            <BlendFunc Src="1" Dst="771" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint />
                        <Position Y="68.6000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition Y="0.4900" />
                        <PreSize X="0.0000" Y="0.0000" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="0.5000" />
                    <Position Y="-16.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="1293648551" Tag="437" IconVisible="False" LeftMargin="86.9375" RightMargin="-253.9375" TopMargin="-76.4200" BottomMargin="72.4200" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="45231341" Tag="438" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.4375" Y="74.4200" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerTarget" ActionTag="1169075245" Alpha="102" Tag="439" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-83.5000" RightMargin="-83.5000" TopMargin="-95.4200" BottomMargin="53.4200" FontSize="36" LabelText="COLLECT" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="167.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="74.4200" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="93.3800" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2900" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_LimitTime" Visible="False" ActionTag="-418128024" Tag="2036" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="218.9600" BottomMargin="103.0400" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="game_time0_1" ActionTag="264420259" Tag="2038" IconVisible="False" LeftMargin="-325.2538" RightMargin="277.2538" TopMargin="-2.3585" BottomMargin="-45.6415" ctype="SpriteObjectData">
                    <Size X="48.0000" Y="48.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-301.2538" Y="-21.6415" />
                    <Scale ScaleX="1.3000" ScaleY="1.3000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_time0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_score1_32" ActionTag="269014693" Tag="2100" IconVisible="False" LeftMargin="86.5000" RightMargin="-253.5000" TopMargin="-66.7600" BottomMargin="62.7600" ctype="SpriteObjectData">
                    <Size X="167.0000" Y="4.0000" />
                    <Children>
                      <AbstractNodeData Name="game_score1_32_0" ActionTag="1384286091" Tag="2101" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-374.0800" RightMargin="374.0800" FlipX="True" ctype="SpriteObjectData">
                        <Size X="167.0000" Y="4.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="-290.5800" Y="2.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="-1.7400" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                        <BlendFunc Src="1" Dst="771" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="170.0000" Y="64.7600" />
                    <Scale ScaleX="0.9000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_score1.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="text_bannerTime" ActionTag="857176946" Alpha="102" Tag="2102" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-43.0000" RightMargin="-43.0000" TopMargin="-85.7600" BottomMargin="43.7600" FontSize="36" LabelText="TIME" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="86.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position Y="64.7600" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_bannerTime" ActionTag="2083376657" Tag="1716" IconVisible="True" TopMargin="25.0000" BottomMargin="-25.0000" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position Y="-25.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="540.0000" Y="103.0400" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3200" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Node_bannerScore" ActionTag="-1218314486" Tag="718" IconVisible="True" LeftMargin="120.0376" RightMargin="959.9624" TopMargin="244.6200" BottomMargin="77.3800" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Image_moveBg" ActionTag="157363941" Alpha="203" Tag="4127" IconVisible="False" LeftMargin="-78.5218" RightMargin="-86.5218" TopMargin="-61.7391" BottomMargin="-61.7391" Scale9Enable="True" LeftEage="30" RightEage="30" TopEage="33" BottomEage="33" Scale9OriginX="30" Scale9OriginY="33" Scale9Width="32" Scale9Height="34" ctype="ImageViewObjectData">
                    <Size X="165.0435" Y="123.4782" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="4.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="ui_btn_S2.png" Plist="ui.plist" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text_bannerTargetMoveNum" ActionTag="1745193476" Tag="435" IconVisible="False" LeftMargin="2.0000" RightMargin="-43.0000" TopMargin="-30.0000" BottomMargin="-30.0000" LabelText="10" ctype="TextBMFontObjectData">
                    <Size X="41.0000" Y="60.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="2.0000" />
                    <Scale ScaleX="1.2000" ScaleY="1.2000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font/ui_num12x.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="game_moves0_63" ActionTag="788376635" Tag="436" IconVisible="False" LeftMargin="-54.9400" RightMargin="9.9400" TopMargin="-21.0000" BottomMargin="-21.0000" ctype="SpriteObjectData">
                    <Size X="45.0000" Y="42.0000" />
                    <Children>
                      <AbstractNodeData Name="game_moves0_63_0" ActionTag="1543883986" Tag="4128" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" ctype="SpriteObjectData">
                        <Size X="45.0000" Y="42.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="22.5000" Y="21.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.5000" />
                        <PreSize X="1.0000" Y="1.0000" />
                        <FileData Type="PlistSubImage" Path="game_moves0.png" Plist="ui.plist" />
                        <BlendFunc Src="770" Dst="1" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-32.4400" />
                    <Scale ScaleX="1.1000" ScaleY="1.1000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="game_moves0.png" Plist="ui.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="120.0376" Y="77.3800" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1111" Y="0.2403" />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="Challenge_Challenge3.png" Plist="ui.plist" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>