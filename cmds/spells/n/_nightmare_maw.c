#include <spell.h>
#include <magic.h>
inherit SPELL;

int num;

void create()
{
    ::create();
    set_spell_name("nightmare maw");
    set_spell_level(([ "innate" : 8 ]));
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS nightmare maw on TARGET");
    set_damage_desc("slashing");
    set_description("This spell summons a Nightmare Maw, one of mindless demons from the seas of Shadow Plane. It will bite into target, continuously tearing their being apart.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_save("fort");
}

string query_cast_string()
{
    return "%^RESET%^%^C244%^As "+caster->QCN+" %^RESET%^%^C105%^c%^C111%^h%^C117%^a%^C153%^n%^C147%^t%^C141%^s%^RESET%^%^C244%^, a %^RESET%^%^C240%^giant black maw %^RESET%^%^C244%^forms behind"+caster->QS+"%^RESET%^%^C244%^.%^CRST%^";
}

spell_effect(int prof)
{
    spell_successful();

    tell_room(place,"%^RESET%^%^C244%^As "+caster->QCN+" %^RESET%^%^C244%^completes the %^RESET%^%^C105%^c%^C111%^h%^C117%^a%^C153%^n%^C147%^t%^RESET%^%^C244%^, a %^RESET%^%^C240%^giant maw %^RESET%^%^C244%^floats towards "+target->QCN+" %^RESET%^%^C244%^and plunges its %^RESET%^%^C240%^t%^C241%^e%^C242%^e%^C241%^t%^C240%^h %^RESET%^%^C244%^into them.%^CRST%^",target);
    tell_object(target,"%^RESET%^%^C244%^As "+caster->QCN+" %^RESET%^%^C244%^completes the %^RESET%^%^C105%^c%^C111%^h%^C117%^a%^C153%^n%^C147%^t%^RESET%^%^C244%^, a %^RESET%^%^C240%^giant maw %^RESET%^%^C244%^floats towards you and plunges its %^RESET%^%^C240%^t%^C241%^e%^C242%^e%^C241%^t%^C240%^h %^RESET%^%^C244%^into them.%^CRST%^",target);
    damage_targ(target, target->return_target_limb(), sdamage,"slashing");
    num = clevel / 8 + 1;
    if(do_save(target,0))
        num/=2;
    call_out("bite_again",ROUND_LENGTH);
}

void bite_again()
{

    if(!objectp(target))
    {
        dest_effect();
        return;
    }

    if(target->query_hp()<0)
    {
        dest_effect();
        return;
    }

    define_base_damage(0);
    tell_room(ENV(target),"%^BOLD%^%^BLACK%^The maw continues to nibble on "+target->QCN+"!%^RESET%^",target);
    tell_object(target,"%^BOLD%^%^BLACK%^The maw nibbles on you!%^RESET%^");
    damage_targ(target, target->return_target_limb(), sdamage/6,"slashing");

    if(num-- < 0)
    {
        dest_effect();
        return;
    }
    else
    {
        call_out("bite_again",ROUND_LENGTH);
    }
}

dest_effect()
{
    if(find_call_out("bite_again") != -1)
        remove_call_out("bite_again");

    if(objectp(target))
    {
        tell_room(ENV(target),"%^BOLD%^%^BLACK%^The maw was nibbling on "+target->QCN+" vanishes.%^RESET%^",target);
        tell_object(target,"%^BOLD%^%^BLACK%^The maw vanishes!%^RESET%^");
    }

    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
