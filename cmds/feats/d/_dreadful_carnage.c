// Chernobog (12/6/22)
// Feat - Dreadful Carnage

#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("WeaponMastery");
    feat_name("dreadful carnage");
    feat_prereq("20 Base Strength, Powerattack");
    feat_desc("Slaying an enemy demoralizes your other nearby foes, leaving them shaken.");
    permanent(1);
    set_required_for(({ }));
}

int allow_shifted() { return 1; }

int prerequisites(object ob){
    if(!objectp(ob)) return 0;
    if(!FEATS_D->has_feat(ob, "powerattack")) return 0;
    if((int)ob->query_base_stats("strength") < 20){
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}


void execute_feat(){
    ::execute_feat();
    dest_effect();
}

void permanent_effects(object ob){
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob){
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void dest_effect(){
    ::dest_effect();
    remove_feat(this_object());
    return;
}