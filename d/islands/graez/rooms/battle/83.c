
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"73",
"northeast" : ROOMS"84",
"southwest" : ROOMS"82",


]));


}

