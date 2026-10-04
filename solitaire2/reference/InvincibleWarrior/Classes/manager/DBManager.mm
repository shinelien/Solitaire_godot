//
//  DBManager.m
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/29.
//

#import <Foundation/Foundation.h>
#include "DBManager.h"
#import "Firebase.h"
#import <AdSupport/AdSupport.h>
#include "GameBackground.h"
#include "cocos2d.h"
#include "EventObserver.h"
using namespace cocos2d;
 
@interface NSDictionary (Expand)
 
- (id)safeStringObjectForKey:(NSString*)key;
 
@end
 
//
//#import "NSDictionary+Expand.h"
 
@implementation NSDictionary (Expand)
 
- (id)safeStringObjectForKey:(NSString*)key {
    id object = [self objectForKey:key];
    // 字典中没key时value为<nil>
    if (![[self allKeys] containsObject:key]) {
        object = nil;
    }
    if ([[object class] isSubclassOfClass:[NSNull class]]) {
        object = nil;
    } else if ([[object class] isSubclassOfClass:[NSNumber class]]) {
        // 判断NSNumber是不是小数
        if (([object doubleValue] - floor([object doubleValue]) < 0.01)) {
            object = [NSString stringWithFormat:@"%ld",(long)[object integerValue]];
        } else {
            object = [NSString stringWithFormat:@"%.2f",[object doubleValue]];
        }
    }
    return object;
}
 
@end


vector<std::string> girlName
{
        "MARY", "PATRICIA", "LINDA", "BARBARA", "ELIZABETH", "JENNIFER", "MARIA", "SUSAN", "MARGARET", "DOROTHY", "LISA", "NANCY", "KAREN", "BETTY", "HELEN", "SANDRA",
        "DONNA", "CAROL", "RUTH", "SHARON", "MICHELLE", "LAURA", "SARAH", "KIMBERLY", "DEBORAH", "JESSICA", "SHIRLEY", "CYNTHIA", "ANGELA", "MELISSA", "BRENDA",
        "AMY", "ANNA", "REBECCA", "VIRGINIA", "KATHLEEN", "PAMELA", "MARTHA", "DEBRA", "AMANDA", "STEPHANIE", "CAROLYN", "CHRISTINE", "MARIE", "JANET", "CATHERINE",
        "FRANCES", "ANN", "JOYCE", "DIANE", "ALICE", "JULIE", "HEATHER", "TERESA", "DORIS", "GLORIA", "EVELYN", "JEAN", "CHERYL", "MILDRED", "KATHERINE", "JOAN",
        "ASHLEY", "JUDITH", "ROSE", "JANICE", "KELLY", "NICOLE", "JUDY", "CHRISTINA", "KATHY", "THERESA", "BEVERLY", "DENISE", "TAMMY", "IRENE", "JANE", "LORI", "RACHEL", "MARILYN",
        "ANDREA", "KATHRYN", "LOUISE", "SARA", "ANNE", "JACQUELINE", "WANDA", "BONNIE", "JULIA", "RUBY", "LOIS", "TINA", "PHYLLIS", "NORMA", "PAULA", "DIANA", "ANNIE", "LILLIAN", "EMILY",
        "ROBIN", "PEGGY", "CRYSTAL", "GLADYS", "RITA", "DAWN", "CONNIE", "FLORENCE", "TRACY", "EDNA", "TIFFANY", "CARMEN", "ROSA", "CINDY", "GRACE", "WENDY", "VICTORIA", "EDITH", "KIM", "SHERRY",
        "SYLVIA", "JOSEPHINE", "THELMA", "SHANNON", "SHEILA", "ETHEL", "ELLEN", "ELAINE", "MARJORIE", "CARRIE", "CHARLOTTE", "MONICA", "ESTHER", "PAULINE", "EMMA", "JUANITA", "ANITA",
        "RHONDA", "HAZEL", "AMBER", "EVA", "DEBBIE", "APRIL", "LESLIE", "CLARA", "LUCILLE", "JAMIE", "JOANNE", "ELEANOR", "VALERIE", "DANIELLE", "MEGAN", "ALICIA", "SUZANNE", "MICHELE",
        "GAIL", "BERTHA", "DARLENE", "VERONICA", "JILL", "ERIN", "GERALDINE", "LAUREN", "CATHY", "JOANN", "LORRAINE", "LYNN", "SALLY", "REGINA", "ERICA", "BEATRICE", "DOLORES", "BERNICE",
        "AUDREY", "YVONNE", "ANNETTE", "JUNE", "SAMANTHA", "MARION", "DANA", "STACY", "ANA", "RENEE", "IDA", "VIVIAN", "ROBERTA", "HOLLY", "BRITTANY", "MELANIE", "LORETTA", "YOLANDA", "JEANETTE",
        "LAURIE", "KATIE", "KRISTEN", "VANESSA", "ALMA", "SUE", "ELSIE", "BETH", "JEANNE", "VICKI", "CARLA", "TARA", "ROSEMARY", "EILEEN", "TERRI", "GERTRUDE", "LUCY", "TONYA", "ELLA", "STACEY",
        "WILMA", "GINA", "KRISTIN", "JESSIE", "NATALIE", "AGNES", "VERA", "WILLIE", "CHARLENE", "BESSIE", "DELORES", "MELINDA", "PEARL", "ARLENE", "MAUREEN", "COLLEEN", "ALLISON", "TAMARA", "JOY",
        "GEORGIA", "CONSTANCE", "LILLIE", "CLAUDIA", "JACKIE", "MARCIA", "TANYA", "NELLIE", "MINNIE", "MARLENE", "HEIDI", "GLENDA", "LYDIA", "VIOLA", "COURTNEY", "MARIAN", "STELLA", "CAROLINE",
        "DORA", "JO", "VICKIE", "MATTIE", "TERRY", "MAXINE", "IRMA", "MABEL", "MARSHA", "MYRTLE", "LENA", "CHRISTY", "DEANNA", "PATSY", "HILDA", "GWENDOLYN", "JENNIE", "JOANNA", "IRIS", "EUNICE",
        "NORA", "MARGIE", "NINA", "CASSANDRA", "LEAH", "PENNY", "KAY", "PRISCILLA", "NAOMI", "CAROLE", "BRANDY", "OLGA", "BILLIE", "DIANNE", "TRACEY", "LEONA", "JENNY", "FELICIA", "SONIA", "MIRIAM",
        "VELMA", "BECKY", "BOBBIE", "VIOLET", "KRISTINA", "TONI", "MISTY", "MAE", "SHELLY", "DAISY", "RAMONA", "SHERRI", "ERIKA", "KATRINA", "CLAIRE", "LINDSEY", "LINDSAY", "GENEVA", "GUADALUPE",
        "BELINDA", "MARGARITA", "SHERYL", "CORA", "FAYE", "ADA", "NATASHA", "SABRINA", "ISABEL", "MARGUERITE", "HATTIE", "HARRIET", "MOLLY", "CECILIA", "KRISTI", "BRANDI", "BLANCHE", "SANDY", "ROSIE",
        "ANGIE", "INEZ", "LYNDA", "MADELINE", "AMELIA", "ALBERTA", "GENEVIEVE", "MONIQUE", "JODI", "JANIE", "MAGGIE", "KAYLA", "SONYA", "JAN", "LEE", "KRISTINE", "CANDACE", "FANNIE", "MARYANN",
        "OPAL", "ALISON", "YVETTE", "MELODY", "LUZ", "SUSIE", "OLIVIA", "FLORA", "SHELLEY", "KRISTY", "MAMIE", "LULA", "LOLA", "VERNA", "BEULAH", "ANTOINETTE", "CANDICE", "JUANA", "JEANNETTE",
        "PAM", "KELLI", "HANNAH", "WHITNEY", "BRIDGET", "KARLA", "CELIA", "LATOYA", "PATTY", "SHELIA", "GAYLE", "DELLA", "VICKY", "LYNNE", "SHERI", "MARIANNE", "KARA", "JACQUELYN", "ERMA", "BLANCA",
        "MYRA", "LETICIA", "PAT", "KRISTA", "ROXANNE", "ANGELICA", "JOHNNI", "ROBYN", "FRANCIS", "ADRIENNE", "ROSALIE", "ALEXANDRA", "BROOKE", "BETHANY", "SADIE", "BERNADETTE", "TRACI", "JODY",
        "KENDRA", "JASMINE", "NICHOLE", "RACHAEL", "CHELSEA", "MABLE", "ERNESTINE", "MURIEL", "MARCELLA", "ELENA", "KRYSTAL", "ANGELINA", "NADINE", "KARI", "ESTELLE", "DIANNA", "PAULETTE", "LORA",
        "MONA", "DOREEN", "ROSEMARIE", "ANGEL", "DESIREE", "ANTONIA", "HOPE", "GINGER", "JANIS", "BETSY", "CHRISTIE", "FREDA", "MERCEDES", "MEREDITH", "LYNETTE", "TERI", "CRISTINA", "EULA", "LEIGH",
        "MEGHAN", "SOPHIA", "ELOISE", "ROCHELLE", "GRETCHEN", "CECELIA", "RAQUEL", "HENRIETTA", "ALYSSA", "JANA", "KELLEY", "GWEN", "KERRY", "JENNA", "TRICIA", "LAVERNE", "OLIVE", "ALEXIS", "TASHA",
        "SILVIA", "ELVIRA", "CASEY", "DELIA", "SOPHIE", "KATE", "PATTI", "LORENA", "KELLIE", "SONJA", "LILA", "LANA", "DARLA", "MAY", "MINDY", "ESSIE", "MANDY", "LORENE", "ELSA", "JOSEFINA", "JEANNIE",
        "MIRANDA", "DIXIE", "LUCIA", "MARTA", "FAITH", "LELA", "JOHANNA", "SHARI", "CAMILLE", "TAMI", "SHAWNA", "ELISA", "EBONY", "MELBA", "ORA", "NETTIE", "TABITHA", "OLLIE", "JAIME", "WINIFRED",
        "KRISTIE",
};

vector<std::string> boyName
{
        "JAMES", "JOHN", "ROBERT", "MICHAEL", "WILLIAM", "DAVID", "RICHARD", "CHARLES", "JOSEPH", "THOMAS", "CHRISTOPHER", "DANIEL", "PAUL", "MARK", "DONALD", "GEORGE", "KENNETH", "STEVEN",
        "EDWARD", "BRIAN", "RONALD", "ANTHONY", "KEVIN", "JASON", "MATTHEW", "GARY", "TIMOTHY", "JOSE", "LARRY", "JEFFREY", "FRANK", "SCOTT", "ERIC", "STEPHEN", "ANDREW", "RAYMOND", "GREGORY",
        "JOSHUA", "JERRY", "DENNIS", "WALTER", "PATRICK", "PETER", "HAROLD", "DOUGLAS", "HENRY", "CARL", "ARTHUR", "RYAN", "ROGER", "JOE", "JUAN", "JACK", "ALBERT", "JONATHAN", "JUSTIN",
        "TERRY", "GERALD", "KEITH", "SAMUEL", "WILLIE", "RALPH", "LAWRENCE", "NICHOLAS", "ROY", "BENJAMIN", "BRUCE", "BRANDON", "ADAM", "HARRY", "FRED", "WAYNE", "BILLY", "STEVE", "LOUIS",
        "JEREMY", "AARON", "RANDY", "HOWARD", "EUGENE", "CARLOS", "RUSSELL", "BOBBY", "VICTOR", "MARTIN", "ERNEST", "PHILLIP", "TODD", "JESSE", "CRAIG", "ALAN", "SHAWN", "CLARENCE", "SEAN",
        "PHILIP", "CHRIS", "JOHNNY", "EARL", "JIMMY", "ANTONIO", "DANNY", "BRYAN", "TONY", "LUIS", "MIKE", "STANLEY", "LEONARD", "NATHAN", "DALE", "MANUEL", "RODNEY", "CURTIS", "NORMAN",
        "ALLEN", "MARVIN", "VINCENT", "GLENN", "JEFFERY", "TRAVIS", "JEFF", "CHAD", "JACOB", "LEE", "MELVIN", "ALFRED", "KYLE", "FRANCIS", "BRADLEY", "JESUS", "HERBERT", "FREDERICK", "RAY",
        "JOEL", "EDWIN", "DON", "EDDIE", "RICKY", "TROY", "RANDALL", "BARRY", "ALEXANDER", "BERNARD", "MARIO", "LEROY", "FRANCISCO", "MARCUS", "MICHEAL", "THEODORE", "CLIFFORD", "MIGUEL",
        "OSCAR", "JAY", "JIM", "TOM", "CALVIN", "ALEX", "JON", "RONNIE", "BILL", "LLOYD", "TOMMY", "LEON", "DEREK", "WARREN", "DARRELL", "JEROME", "FLOYD", "LEO", "ALVIN", "TIM", "WESLEY",
        "GORDON", "DEAN", "GREG", "JORGE", "DUSTIN", "PEDRO", "DERRICK", "DAN", "LEWIS", "ZACHARY", "COREY", "HERMAN", "MAURICE", "VERNON", "ROBERTO", "CLYDE", "GLEN", "HECTOR", "SHANE",
        "RICARDO", "SAM", "RICK", "LESTER", "BRENT", "RAMON", "CHARLIE", "TYLER", "GILBERT", "GENE", "MARC", "REGINALD", "RUBEN", "BRETT", "ANGEL", "NATHANIEL", "RAFAEL", "LESLIE", "EDGAR",
        "MILTON", "RAUL", "BEN", "CHESTER", "CECIL", "DUANE", "FRANKLIN", "ANDRE", "ELMER", "BRAD", "GABRIEL", "RON", "MITCHELL", "ROLAND", "ARNOLD", "HARVEY", "JARED", "ADRIAN", "KARL",
        "CORY", "CLAUDE", "ERIK", "DARRYL", "JAMIE", "NEIL", "JESSIE", "CHRISTIAN", "JAVIER", "FERNANDO", "CLINTON", "TED", "MATHEW", "TYRONE", "DARREN", "LONNIE", "LANCE", "CODY", "JULIO",
        "KELLY", "KURT", "ALLAN", "NELSON", "GUY", "CLAYTON", "HUGH", "MAX", "DWAYNE", "DWIGHT", "ARMANDO", "FELIX", "JIMMIE", "EVERETT", "JORDAN", "IAN", "WALLACE", "KEN", "BOB", "JAIME",
        "CASEY", "ALFREDO", "ALBERTO", "DAVE", "IVAN", "JOHNNIE", "SIDNEY", "BYRON", "JULIAN", "ISAAC", "MORRIS", "CLIFTON", "WILLARD", "DARYL", "ROSS", "VIRGIL", "ANDY", "MARSHALL",
        "SALVADOR", "PERRY", "KIRK", "SERGIO", "MARION", "TRACY", "SETH", "KENT", "TERRANCE", "RENE", "EDUARDO", "TERRENCE", "ENRIQUE", "FREDDIE", "WADE", "AUSTIN", "STUART", "FREDRICK",
        "ARTURO", "ALEJANDRO", "JACKIE", "JOEY", "NICK", "LUTHER", "WENDELL", "JEREMIAH", "EVAN", "JULIUS", "DANA", "DONNIE", "OTIS", "SHANNON", "TREVOR", "OLIVER", "LUKE", "HOMER",
        "GERARD", "DOUG", "KENNY", "HUBERT", "ANGELO", "SHAUN", "LYLE", "MATT", "LYNN", "ALFONSO", "ORLANDO", "REX", "CARLTON", "ERNESTO", "CAMERON", "NEAL", "PABLO", "LORENZO", "OMAR",
        "WILBUR", "BLAKE", "GRANT", "HORACE", "RODERICK", "KERRY", "ABRAHAM", "WILLIS", "RICKEY", "JEAN", "IRA", "ANDRES", "CESAR", "JOHNATHAN", "MALCOLM", "RUDOLPH", "DAMON", "KELVIN",
        "RUDY", "PRESTON", "ALTON", "ARCHIE", "MARCO", "WM", "PETE", "RANDOLPH", "GARRY", "GEOFFREY", "JONATHON", "FELIPE", "BENNIE", "GERARDO", "ED", "DOMINIC", "ROBIN", "LOREN", "DELBERT",
        "COLIN", "GUILLERMO", "EARNEST", "LUCAS", "BENNY", "NOEL", "SPENCER", "RODOLFO", "MYRON", "EDMUND", "GARRETT", "SALVATORE", "CEDRIC", "LOWELL", "GREGG", "SHERMAN", "WILSON", "DEVIN",
        "SYLVESTER", "KIM", "ROOSEVELT", "ISRAEL", "JERMAINE", "FORREST", "WILBERT", "LELAND", "SIMON", "GUADALUPE", "CLARK", "IRVING", "CARROLL", "BRYANT", "OWEN", "RUFUS", "WOODROW", "SAMMY",
        "KRISTOPHER", "MACK", "LEVI", "MARCOS", "GUSTAVO", "JAKE", "LIONEL", "MARTY", "TAYLOR", "ELLIS", "DALLAS", "GILBERTO", "CLINT", "NICOLAS", "LAURENCE", "ISMAEL", "ORVILLE", "DREW", "JODY",
        "ERVIN", "DEWEY", "AL", "WILFRED", "JOSH", "HUGO", "IGNACIO", "CALEB", "TOMAS", "SHELDON", "ERICK", "FRANKIE", "STEWART", "DOYLE", "DARREL", "ROGELIO", "TERENCE", "SANTIAGO", "ALONZO",
        "ELIAS", "BERT", "ELBERT", "RAMIRO", "CONRAD", "PAT", "NOAH", "GRADY", "PHIL", "CORNELIUS", "LAMAR", "ROLANDO", "CLAY", "PERCY", "DEXTER", "BRADFORD", "MERLE", "DARIN", "AMOS", "TERRELL",
        "MOSES", "IRVIN", "SAUL", "ROMAN", "DARNELL", "RANDAL", "TOMMIE", "TIMMY", "DARRIN", "WINSTON", "BRENDAN", "TOBY", "VAN", "ABEL", "DOMINICK", "BOYD", "COURTNEY", "JAN", "EMILIO",
        "ELIJAH", "CARY", "DOMINGO", "SANTOS", "AUBREY", "EMMETT", "MARLON", "EMANUEL", "JERALD", "EDMOND",
};

DBManager* DBManager::_DBManager = nullptr;

DBManager* DBManager::getInstance()
{
    if(!_DBManager)
    {
        _DBManager = new DBManager();
    }
    return _DBManager;
}


DBManager::DBManager()
{
    
    FIRDatabaseReference *ref = [[FIRDatabase database] reference];
    
    NSString *userID = [UIDevice currentDevice].identifierForVendor.UUIDString;
    _uuid = [userID UTF8String];
    nameVec.push_back(girlName);
    nameVec.push_back(boyName);
    _me = getPlayerName();
    
    //年月日
    auto tm = DATA_M->getContentTime();
    auto year = tm->tm_year + 1900;
    auto mon = tm->tm_mon + 1;
    auto day = tm->tm_mday;
    
    _dailyKey = "d_2021_5_29"; // 默认是 rob//StringUtils::format("d_%d_%d_%d",year,mon,day);
    _dailyKeyTs = 0;
    
    _p1 = 0;
    _p2 = 0;
    
    auto _refHandle = [[ref child:@"d_key_map"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
    
        NSDictionary *postDict = snapshot.value;
        NSString*d_key = postDict[@"d_key"];
        _dailyKey = d_key!=nil?[d_key UTF8String]:_dailyKey;
        NSNumber*d_key_ts = postDict[@"d_key_ts"];
        _dailyKeyTs = d_key_ts!=nil?[(d_key_ts) longValue]:_dailyKeyTs;
        
        log("DBManager: DBManager() _dailyKey: %s, _dailyKeyTs: %d",_dailyKey.c_str(),_dailyKeyTs);
        getRank("p1");
        
        queryMe();
      // ...
    }];
}

DBManager::~DBManager()
{
    
}

std::string DBManager::getPlayerName()
{
    auto name = GETSTR("player_name","");
    if(name == "")
    {
        auto xRand = random(0, 1);
        auto vec = nameVec.at(xRand);
        
        auto nameId = random(0, (int)vec.size()-1);
        name = vec.at(nameId);
    }
    return name;
}

void DBManager::getRank(std::string p)
{
    FIRDatabaseReference *ref = [[FIRDatabase database] reference];
    
    NSString* d_url = [ref URL];
    
//    FIRDatabaseReference*parent = [ref parent];
//    FIRDatabaseReference*root = [ref root];
//    NSString*key = [ref key];
//    FIRDatabase*database = [ref database];
//    //"users" "ranks" "d_key_map"
//    FIRDatabaseReference* users = [ref child:@"users"];
//    FIRDatabaseReference* ranks = [ref child:@"ranks"];
//    FIRDatabaseReference* d_key_map = [ref child:@"d_key_map"];
//    FIRDatabaseReference* d_key= [d_key_map child:@"d_key"];
//    FIRDatabaseReference* d_key_ts=  [d_key_map child:@"d_key_ts"];
//    NSLog(@"DBManager: getRank()  d_url%@", d_url);
    
    
    auto num = ScoreManager::getInstance()->getWinTotalCNT(true);
    bool isRobList = num < 3;
    string queryKey = isRobList?"d_2021_5_29":_dailyKey;
    [[[[[ref child:@"ranks"] child:[NSString stringWithUTF8String: queryKey.c_str()]] queryOrderedByChild:[NSString stringWithUTF8String: p.c_str()]] queryLimitedToLast:300] observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        // Get user value
        NSLog(@"DBManager: getRank()  Get user value");
        NSEnumerator<FIRDataSnapshot *>* array = [snapshot children];
        ValueVector vec;
        
        for (FIRDataSnapshot *item in array)
        {

            
            NSString* key = [item key];
            log("DBManager: getRank() FIRDataSnapshot%s",[key UTF8String]);
            NSDictionary *postDict = item.value;
            NSString*name = postDict[@"name"];
            NSNumber*p1 = postDict[@"p1"];
            NSNumber*p2 = postDict[@"p2"];
            NSNumber*playerLv = postDict[@"playerLv"];
            NSNumber*fashTankIdx = postDict[@"fashTankIdx"];
            NSString* cy = postDict[@"cy"];
            NSArray* fishArray = postDict[@"fishArray"];
            
            ValueVector fishVec;
            for(int i = 0;i < fishArray.count;++i)
            {
                NSNumber* v = [fishArray objectAtIndex:i];
                int k = [v intValue];
                fishVec.push_back(Value(k));
            }
            
            NSArray* isDailyArray =postDict[@"isDailyArray"];
            ValueVector isDailyVec;
            for(int i = 0;i < isDailyArray.count;++i)
            {
                NSNumber* v = [isDailyArray objectAtIndex:i];
                int k = [v intValue];
                isDailyVec.push_back(Value(k));
                
            }
            NSArray* isFashTankUnlockArray = postDict[@"isFashTankUnlockArray"];
            ValueVector isFashTankUnlockVec;
            for(int i = 0;i < isFashTankUnlockArray.count;++i)
            {
                NSNumber* v = [isFashTankUnlockArray objectAtIndex:i];
                int k = [v intValue];
                isFashTankUnlockVec.push_back(Value(k));
            }
            ValueMap valueMap{
                {"key",Value([key UTF8String])},
                {"name",Value([name UTF8String])},
                {"p1",Value([p1 intValue])},
                {"p2",Value([p2 intValue])},
                {"playerLv",Value([playerLv intValue])},
                {"fashTankIdx",Value([fashTankIdx intValue])},
                {"cy",Value([cy UTF8String])},
                {"fishArray",Value(fishVec)},
                {"isDailyArray",Value(isDailyVec)},
                {"isFashTankUnlockArray",Value(isFashTankUnlockVec)},
            };
            Value value(valueMap);
            
            vec.push_back(value);
            //std::string jsonStr(valueMap2["list"].asString());
        }
        
        ValueMap valueMap2{
            {"msg",Value("msg_rank_list")},
            {"list",Value(vec)},
        };
        EVENT_M->sendEvent("event_game_update_rank",valueMap2);
        // ...
      } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"DBManager: getRank()  error%@", error.localizedDescription);
          ValueMap valueMap{
              {"msg",Value("msg_rank_list_cancel")},
          };
          EVENT_M->sendEvent("event_game_update_rank",valueMap);
          
      }];
    //Task<DataSnapshot> myMostViewedPostsQuery = _databaseRanksReference.child(queryKey).orderByChild(p).limitToLast(300).get();
}

void DBManager::queryMe()
{
    FIRDatabaseReference *ref = [[FIRDatabase database] reference];
    [[[[ref child:@"ranks"] child:[NSString stringWithUTF8String: _dailyKey.c_str()]] child: [NSString stringWithUTF8String: _uuid.c_str()]]  observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        NSDictionary *postDict = snapshot.value;
        if(![[postDict class] isSubclassOfClass:[NSNull class]])
        {
            NSNumber * sp1 = postDict[@"p1"];
            _p1 = [sp1!=nil?sp1:0 intValue];
            NSNumber * sp2 = postDict[@"p2"];
            _p2 = [sp2!=nil?sp2:0 intValue];
            log("DBManager: queryMe() _p1: %d, _p2: %d",_p1,_p2);
        }
        else
        {
        }
        // ...
      } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"DBManager:  queryMe()%@", error.localizedDescription);
      } ];
}

void DBManager::setUser(int p1, int p2, int playerLv, int fashTankIdx,std::string name)
{
    string cy = UIUtils::getCountryID();
    auto idx = DATA_M->getCurrentFashTankIdx();
    auto fishVec = DATA_M->getFishTypeVec(idx);
    auto fishLength = fishVec.size();
    NSMutableArray *fishArray=[NSMutableArray arrayWithCapacity:fishLength];
    for(int i = 0;i < fishLength;++i)
    {
        [fishArray addObject:[NSNumber numberWithInt:fishVec.at(i)]];
    }

    auto fashTank = SCENE_M->getGameBackground();
    auto isDailyVec = fashTank->getFishIsDaily();
    auto isDailyLength = isDailyVec.size();
    NSMutableArray *isDailyArray=[NSMutableArray arrayWithCapacity:isDailyLength];
    for(int i = 0;i < isDailyLength;++i)
    {
        [isDailyArray addObject:[NSNumber numberWithInt:isDailyVec.at(i)]];
    }
    //isFashTankUnlockArray
    auto isFashTankUnlockVec = DATA_M->getFashTankUnlockVec(idx);
    auto isFashTankUnlockLength = isFashTankUnlockVec.size();
    NSMutableArray *isFashTankUnlockArray=[NSMutableArray arrayWithCapacity:isFashTankUnlockLength];
    for(int i = 0;i < isFashTankUnlockLength;++i)
    {
        [isFashTankUnlockArray addObject:[NSNumber numberWithInt:isFashTankUnlockVec.at(i)]];
    }
    
    //FIRDatabaseReference 实例：
    FIRDatabaseReference *ref;
    ref = [[FIRDatabase database] reference];
    
    NSString *idfa = [NSString stringWithUTF8String: _uuid.c_str()];
    
    //更新数据 "users" "ranks" "d_key_map"
    NSString* name2 = [NSString stringWithUTF8String: name.c_str()];
    NSString* myName = [NSString stringWithUTF8String: _me.c_str()];;
    if(name != "")
    {
        myName = name2;
    }
    
    NSDictionary *post = @{@"name": myName,
                           @"p1": [NSNumber numberWithInt:p1],
                           @"p2": [NSNumber numberWithInt:p2],
                           @"playerLv": [NSNumber numberWithInt:playerLv],
                           @"fashTankIdx": [NSNumber numberWithInt:fashTankIdx],
                           @"cy": [NSString stringWithUTF8String: cy.c_str()],
                           @"fishArray": fishArray,
                           @"isDailyArray": isDailyArray,
                           @"isFashTankUnlockArray": isFashTankUnlockArray};
    //更新
    [[[ref child:@"users"] child: idfa] updateChildValues:post withCompletionBlock:^(NSError *error, FIRDatabaseReference *ref2) {
        if (error) {
          NSLog(@"DBManager: setUser() Data could not be saved: %@", error);
        } else {
            
        }
      }];
    
//    NSString* queryKey = @"d_2021_5_29";
//    auto num = ScoreManager::getInstance()->getWinTotalCNT(true);
//    bool isRobList = num < 3;
    //NSString *userID = [FIRAuth auth].currentUser.uid;
//    if(isRobList)
//    {
//        [[[[ref child:@"ranks"] child: queryKey]child:idfa] observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
//          // Get user value
//            NSDictionary *postDict = snapshot.value;
//            if(![[postDict class] isSubclassOfClass:[NSNull class]])
//            {
//                NSString * sname = [postDict safeStringObjectForKey:@"name"];
//                sname = sname!=nil?sname:@"Player";
//                NSNumber* sp1 = [postDict safeStringObjectForKey:@"p1"];
//                sp1 = sp1!=nil?sp1:0;
//                NSNumber * sp2 = [postDict safeStringObjectForKey:@"p2"];
//                sp2 = sp2!=nil?sp2:0;
//
//
//                int isp1 = [(sp1) intValue];
//                int isp2 = [(sp2) intValue];
//                int fp1 = p1 + isp1;
//                int fp2 = p2 + isp2;
//                NSDictionary *post = @{
//                                       @"p1": [NSNumber numberWithInt:fp1],
//                                       @"p2": [NSNumber numberWithInt:fp2]};
//                //更新
//                [[[[ref child:@"ranks"] child: [NSString stringWithUTF8String: _dailyKey.c_str()]]child:idfa] updateChildValues:post withCompletionBlock:^(NSError *error, FIRDatabaseReference *ref) {
//                    if (error) {
//                      NSLog(@"DBManager: setUser() Data could not be saved:error  %@", error);
//                    } else {
//                      NSLog(@"DBManager: setUser() Data saved successfully.");
//                        _p1 = fp1;
//                        _p2 = fp2;
//                    }
//                  }];
//            }
//
//            NSLog(@"DBManager: setUser() postDict class isSubclassOfClass NSNull class");
//          // ...
//        } withCancelBlock:^(NSError * _Nonnull error) {
//          NSLog(@"DBManager: setUser() %@", error.localizedDescription);
//        }];
//    }
     
    [[[[ref child:@"ranks"] child: [NSString stringWithUTF8String: _dailyKey.c_str()]]child:idfa] observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
      // Get user value
        NSDictionary *postDict = snapshot.value;
        if(![[postDict class] isSubclassOfClass:[NSNull class]])
        {
            NSString * sname = [postDict safeStringObjectForKey:@"name"];
            sname = sname!=nil?sname:@"Player";
            NSNumber* sp1 = [postDict safeStringObjectForKey:@"p1"];
            sp1 = sp1!=nil?sp1:0;
            NSNumber * sp2 = [postDict safeStringObjectForKey:@"p2"];
            sp2 = sp2!=nil?sp2:0;
            
            
            int isp1 = [(sp1) intValue];
            int isp2 = [(sp2) intValue];
            int fp1 = p1 + isp1;
            int fp2 = p2 + isp2;
            NSDictionary *post = @{
                                   @"p1": [NSNumber numberWithInt:fp1],
                                   @"p2": [NSNumber numberWithInt:fp2]};
            //更新
            [[[[ref child:@"ranks"] child: [NSString stringWithUTF8String: _dailyKey.c_str()]]child:idfa] updateChildValues:post withCompletionBlock:^(NSError *error, FIRDatabaseReference *ref) {
                if (error) {
                  NSLog(@"DBManager: setUser() Data could not be saved:error  %@", error);
                } else {
                  NSLog(@"DBManager: setUser() Data saved successfully.");
                    _p1 = fp1;
                    _p2 = fp2;
                }
              }];
        }
        else
        {
            //添加用户
            [[[[ref child:@"ranks"] child: [NSString stringWithUTF8String: _dailyKey.c_str()]] child:idfa] setValue:post withCompletionBlock:^(NSError *error, FIRDatabaseReference *ref2) {
                if (error) {
                  NSLog(@"DBManager: setUser() Data could not be saved: %@", error);
                } else {
                    
                }
              }];
            _p1 = p1;
            _p2 = p2;
            NSLog(@"DBManager: setUser() postDict class isSubclassOfClass NSNull class");
        }
      // ...
    } withCancelBlock:^(NSError * _Nonnull error) {
      NSLog(@"DBManager: setUser() error %@", error.localizedDescription);
    }];
    
}
