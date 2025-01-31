//Too old to matter -- Tlaloc --

//      Network Screening Daemon [v0.1]
//      Thorn@Shadowgate
//      12/15/94
//      Daemons for Network Security
//      screen_d.c

#include <std.h>
#include <security.h>
#include <daemons.h>

inherit DAEMON;

mapping bad_user, bad_mud;
int counter;

process_incoming();
validate_user();
int cut_off_mud(string bad_mud);
cut_all_services();
cut_off_user(string intermole);
cut_off_site();  //     Unimplimented as of yet -- Thorn
set_bad_mud(string str);
set_bad_user(string user, string mud_name);
set_closedown(string str);
clear_all();
redeem_mud(string mud_name);
redeem_user(string user_name);

int save_file;

save() {
        save_object("/adm/etc/intermud_screen");
}

restore() {
        restore_object("/adm/etc/intermud_screen");
}

void create() {
        seteuid(getuid());
        bad_user = ([]);
        bad_mud = ([]);
        restore();
}

int set_bad_user(string user, string host) {
//      if(previous_object()->getuid() != UID_ROOT) return 0;
        string b_user;
        b_user = lower_case(user+"@"+host);
        bad_user[b_user] = 1;
        log_file("intermud", "["+ctime(time())+"] ScreenDaemon enabled USER block on "+b_user+"\n");
        save();
        return 1;
}

void set_bad_mud(string host) {
//      if(previous_object()->getuid() != UID_ROOT) return;
        bad_mud[host] = 1;
        log_file("intermud", "["+ctime(time())+"] ScreenDaemon enabled MUD block on "+host+"\n");
        save();
}

int redeem_user(mixed str) {
//      if(previous_object()->getuid() != UID_ROOT) return 0;
        map_delete(bad_user, lower_case(str));
        log_file("intermud", "["+ctime(time())+"] ScreenDaemon disabled USER block on "+bad_user+"\n");
        save();
        return 1;
}

int redeem_mud(mixed host) {
//      if(previous_object()->getuid() != UID_ROOT) return 0;
        if(bad_mud[host] != 1) return -1;
        map_delete(bad_mud, host);
        log_file("intermud", "["+ctime(time())+"] ScreenDaemon disabled MUD block on "+host+"\n");
        save();
        return 1;
}

string *list_bad_users() {
        string *user_list;
        user_list = keys(bad_user);
        return user_list;
}

string *list_bad_muds() {
        string *mud_list;
        mud_list = keys(bad_mud);
        return mud_list;
}

int process_incoming(string user, string mud) {
        string full_user;
        full_user = lower_case(user+"@"+mud);
        if(bad_mud[mud] == 1) return 0;
        if(bad_user[full_user] == 1) return -1;
//      if(closedown() == 1) return 0;
        return 1;
}

void set_counter(int a) {
        counter = a;
}

int query_counter() {
        return counter;
}


void clear_all() {
        bad_user = ([]);
        bad_mud = ([]);
        log_file("intermud", "**["+ctime(time())+"] ScreenDaemon cleared ALL iblocked entries!**\n");
        save();
}
