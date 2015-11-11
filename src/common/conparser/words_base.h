// Copyright (C) University of Oxford 2010
/*===============================================================
 *
 * stanford dependencies in ZPar
 * Authors: Miguel Ballesteros and Yue Zhang
 * UPF-Spain and SUTD-Singapore
 *
 *==============================================================*/

//static copulateVerbs({"be", "being", "been", "am", "are", "r", "is", "ai", "was", "were", "'m", "'re", "'s", "s", "seem", "seems", "seemed", "appear", "appears", "appeared", "stay", "stays", "stayed", "remain", "remains", "remained", "resemble", "resembles", "resembled", "become", "becomes", "became"};

//Miguel
static CWord g_word_here("here");
static CWord g_word_there("there");
static CWord g_word_mondays("Mondays");
static CWord g_word_monday("Monday");
static CWord g_word_tuesdays("Tuesdays");
static CWord g_word_tuesday("Tuesday");
static CWord g_word_wednesdays("Wednesdays");
static CWord g_word_wednesday("Wednesday");
static CWord g_word_thursdays("Thursdays");
static CWord g_word_thursday("Thursday");
static CWord g_word_fridays("Fridays");
static CWord g_word_friday("Friday");
static CWord g_word_saturdays("Saturdays");
static CWord g_word_saturday("Saturday");
static CWord g_word_sundays("Sundays");
static CWord g_word_sunday("Sunday");
static CWord g_word_years("years");
static CWord g_word_year("year");
static CWord g_word_months("months");
static CWord g_word_month("month");
static CWord g_word_weeks("weeks");
static CWord g_word_week("week");
static CWord g_word_days("days");
static CWord g_word_day("day");
static CWord g_word_mornings("mornings");
static CWord g_word_morning("morning");
static CWord g_word_evenings("evenings");
static CWord g_word_evening("evening");
static CWord g_word_nights("nights");
static CWord g_word_night("night");
static CWord g_word_january("January");
static CWord g_word_jan("Jan."); //...Jan+something
static CWord g_word_february("February");
static CWord g_word_feb("Feb.");//... Feb+something
static CWord g_word_march("March");
static CWord g_word_mar("Mar.");//... Mar+something
static CWord g_word_april("April");
static CWord g_word_apr("Apr.");//... Apr+something
static CWord g_word_may("May");
static CWord g_word_june("June");
static CWord g_word_july("July");
static CWord g_word_august("August");
static CWord g_word_aug("Aug.");//... Apr+something
static CWord g_word_september("September");
static CWord g_word_sept("Sept.");//... Apr+something
static CWord g_word_october("October");
static CWord g_word_oct("Oct.");//... Apr+something
static CWord g_word_november("November");
static CWord g_word_nov("Nov.");//... Apr+something
static CWord g_word_december("December");
static CWord g_word_dec("Dec.");//... Apr+something
static CWord g_word_today("today");
static CWord g_word_yesterday("yesteday");
static CWord g_word_tomorrow("tomorrow");
static CWord g_word_spring("spring");
static CWord g_word_summer("summer");
static CWord g_word_fall("fall");
static CWord g_word_autumn("autumn");
static CWord g_word_winter("winter");

static CWord g_word_lot("lot");


  /*private static final String beAuxiliaryRegex =
    "/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai)$/";*/

//Miguel
static CWord g_word_am("am");
static CWord g_word_is("is");
static CWord g_word_are("are");
static CWord g_word_r("r");
static CWord g_word_be("be");
static CWord g_word_being("being");
static CWord g_word_aps("'s");
static CWord g_word_apre("'re");
static CWord g_word_apm("m");
static CWord g_word_was("was");
static CWord g_word_were("were");
static CWord g_word_been("been");
static CWord g_word_s("s");
static CWord g_word_ai("ai");

//private static final String passiveAuxWordRegex =
    //"/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai|seem|seems|seemed|seeming|appear|appears|appeared|become|becomes|became|becoming|get|got|getting|gets|gotten|remains|remained|remain)$/";


//private static final String copularWordRegex =
//    "/^(?i:am|is|are|r|be|being|'s|'re|'m|was|were|been|s|ai|seem|seems|seemed|seeming|appear|appears|
//appeared|stay|stays|stayed|remain|remains|remained|resemble|resembles|resembled|resembling|become|becomes|became|becoming)$/";
//the first ones are already above. Miguel
static CWord g_word_seem("seem");
static CWord g_word_seems("seems");
static CWord g_word_seemed("seemed");
static CWord g_word_seeming("seeming");
static CWord g_word_appear("appear");
static CWord g_word_appears("appears");
static CWord g_word_appeared("appeared");
static CWord g_word_stay("stay");
static CWord g_word_stays("stays");
static CWord g_word_stayed("stayed");
static CWord g_word_remain("remain");
static CWord g_word_remains("remains");
static CWord g_word_remained("remained");
static CWord g_word_resemble("resemble");
static CWord g_word_resembles("resembles");
static CWord g_word_resembled("resembled");
static CWord g_word_resembling("resembling");
static CWord g_word_become("become");
static CWord g_word_becomes("becomes");
static CWord g_word_became("became");
static CWord g_word_becoming("becoming");

static CWord g_word_get("get");
static CWord g_word_got("got");
static CWord g_word_getting("getting");
static CWord g_word_gets("gets");
static CWord g_word_gotten("gotten");

 /*private static final String haveRegex =
    "/^(?i:have|had|has|having)$/";*/
 //Miguel
 static CWord g_word_have("have");
 static CWord g_word_had("had");
 static CWord g_word_has("has");
 static CWord g_word_having("having");

   /*private static final String stopKeepRegex =
    "/^(?i:stop|stops|stopped|stopping|keep|keeps|kept|keeping)$/";*/

 static CWord g_word_stop("stop");
 static CWord g_word_stops("stops");
 static CWord g_word_stopped("stopped");
 static CWord g_word_stopping("stopping");
 static CWord g_word_keep("keep");
 static CWord g_word_keeps("keeps");
 static CWord g_word_kept("kept");
 static CWord g_word_keeping("keeping");


//extras
 static CWord g_word_either("either");
 static CWord g_word_neither("neither");
 static CWord g_word_both("both");

 static CWord g_word_all("all");
 static CWord g_word_each("each");



 //only|just|merely
 static CWord g_word_only("only");
 static CWord g_word_just("just");
 static CWord g_word_merely("merely");

 static CWord g_word_not("not");
 static CWord g_word_nt("n't");

 static CWord g_word_comma(",");

 static CWord g_word_as("as");
 static CWord g_word_that("that");
 static CWord g_word_how("how");
 static CWord g_word_whether("whether");

 static CWord g_word_order("order");

 static CWord g_word_two_dots(":");
 static CWord g_word_slash("/");

 static CWord g_word_dot(".");
 static CWord g_word_dollar("$");
 static CWord g_word_hash("#");

 static CWord g_word_asterisc("*");
 static CWord g_word_hyphen("-");
 static CWord g_word_hyphen2("--");
 static CWord g_word_lowhyphen("_");
 static CWord g_word_perc("%");

 static CWord g_word_at("at");
 static CWord g_word_in("in");
 static CWord g_word_In("In");

 static CWord g_word_to("to");
 static CWord g_word_addition("addition");
 static CWord g_word_so("so");

 static CWord g_word_quote("'");
 static CWord g_word_quotes("``");
 static CWord g_word_squotes("''");

 static CWord g_word_where("where");
 static CWord g_word_why("why");
 static CWord g_word_when("when");
 static CWord g_word_notwithstanding("notwithstanding");

 static CWord g_word_old("old");
 static CWord g_word_well("well");
 static CWord g_word_rather("rather");
 static CWord g_word_instead("instead");
 static CWord g_word_than("than");
  static CWord g_word_of("of");

  static CWord g_word_such("such");
  static CWord g_word_because("because");
  static CWord g_word_Because("because");
  static CWord g_word_least("least");
  static CWord g_word_due("due");
  static CWord g_word_Due("Due");



//static CWord g_word_lot("lot"); //?

