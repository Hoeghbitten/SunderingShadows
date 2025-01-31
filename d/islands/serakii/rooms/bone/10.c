#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_tower.c";

void create(){
   ::create();
   has_a_clue=3;

set_exits(([
"northeast" : BONE"11",
"down" : BONE"9",

]));

add_item("staircase","%^C240%^This staircase, made of %^C244%^wrought iron%^C240%^ is an absolute work of art. The balusters are made to look like %^C248%^old columns%^C240%^ with %^C064%^ivy %^C240%^crawling along them and even %^C124%^small birds%^C240%^ made of precious %^C160%^gems %^C240%^are placed around it.%^CRST%^");
   set_long(::query_long()+"\n%^C239%^A beautifully wrought iron staircase is here.%^CRST%^\n");
}
