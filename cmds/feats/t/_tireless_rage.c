#include <std.h>
#include <daemons.h>
inherit FEAT;

void create()
{
   ::create();
   feat_type("permanent");
   feat_category("Rampage");
   feat_name("tireless rage");
   feat_prereq("Barbarian L17");
   feat_desc("With this feat the barbarian will no longer be fatigued at the end of raging.");
   permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
   if(!objectp(ob)) { return 0; }
   if(ob->query_class_level("barbarian") < 17)
   {
      dest_effect();
      return 0;
   }
    return ::prerequisites(ob);
}

void execute_feat()
{
   ::execute_feat();
   dest_effect();
}

void permanent_effects(object ob)
{
   ::permanent_effects(ob);
   dest_effect();
   return;
}

void reverse_permanent_effects(object ob)
{
   ::reverse_permanent_effects(ob);
   dest_effect();
   return;
}

void dest_effect()
{
   ::dest_effect();
   remove_feat(TO);
   return;
}
