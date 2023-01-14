//Coded by Bane//
#include <std.h>
inherit ROOM;
void create(){
    ::create();
    set_terrain(VILLAGE);
    set_travel(BACK_ALLEY);
    set_name("Dirt road");
    set_short("A dirt road");
    set_long(
        "%^BOLD%^A dirt road%^RESET%^
You are standing on one of the back roads of Systyquah.  The "+
        "street leads off to the northeast, northwest and southeast "+
        "here.  You can see a large wooden hut to the east side of the "+
        "road.  You can see numerous trolls and other creatures "+
        "walking through the roads in troop formation, obviously "+
	"preparing for a huge battle."
    );
    set_property("indoors",0);
    set_property("light",2);
    set_smell("default","The breeze carries a rank, nauseating smell.");
    set_listen("default","You hear the shouts of bugbears and troll war parties.");
    set_exits( ([
        "southeast":"/d/laerad/parnelli/systyquah/sys062",
	"northeast":"/d/laerad/parnelli/systyquah/sys060",
	"northwest":"/d/laerad/parnelli/systyquah/sys057"
    ]) );
}
void reset(){
    ::reset();
    /*if(!present("guard")){
	new("/d/laerad/mon/trollg2")->move(this_object());
    }*/
}
