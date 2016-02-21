// mei_po.c
#include <ansi.h>

inherit NPC;

string marry();
string unmarry();

void create()
{
        set_name("ý��", ({ "mei_po" }) );
        set("title", "����ׯ");
        set("gender", "Ů��" );
        set("age", 43);
        set("long",
                "һλ�����ܸɵ���ý��\n");
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("inquiry", ([
                "��Լ" : "�ǰ�... ����Ϳ��Ե޽�ͽ����Լ",
        ]) );
        set_skill("literate", 70);
        set_skill("dodge", 500);
        set_skill("unarmed", 300);
        setup();
        add_money("gold", 5);
}

void init()
{
        object ob;

        ::init();
//        if( interactive(ob = this_player()) && !is_fighting() ) {
//                remove_call_out("greeting");
//                call_out("greeting", 1, ob);
//        }
        add_action("do_marry", "marry");
        add_action("do_unmarry", "unmarry");
}

int do_marry(string arg) {
        object marry_card1,marry_card2, obj, me;
        object *list,ob;
        int i, have_marry;
//        string markname1;

        me = this_player();

        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
              if (((string)list[i]->query("id")) == "marrycard")
                return notify_fail(
                "���Ѿ��ͱ����л�Լ�˰�?���ﲻ�����ػ�ġ�\n");
        }
        
        if(!arg || !objectp(obj = present(arg, environment(me)))
                || !find_player(arg) )
                return notify_fail("�����˭�޽���Ե��\n");


        if( !environment()
        ||      base_name(environment()) != query("startroom") )
             return notify_fail(
                "���Ǳ�Ǹ��������һ�µ�����ׯ�����Ұɡ�\n");


        if( !living(obj) )
                return notify_fail(obj->name() + 
                "�Ѿ��޷�����޽���Ե�ˡ�\n"); 

        if( (me->query("age") < 17) || (obj->query( "age" ) < 17) )
                return notify_fail( 
	    "�����������涨����17�겻׼��飬�������ӿɲ���Υ�����¡�\n");

        if((string)obj->query("gender")== (string)me->query("gender"))
                return notify_fail("�㲻��" + RED"AIDS"NOR + "��\n");

        if(obj==me)     return notify_fail("�㲻�ܺ��Լ��޽��Լ��\n");

//        markname1 = "marks/" + me->name(1);
        if( userp(obj) && !((object)obj->query("marks/"+me->name(1)))){
                message_vision(MAG "\n$N����$n˵����" 
                    + RANK_D->query_self(me) 
                    + me->name() + "��Ը���"
                    + RANK_D->query_respect(obj) + 
                "��Ϊ��\n\n"NOR, me,obj);           
//        if( objectp(old_target = me->query_temp("t_couple")) )
//                        tell_object(old_target, YEL + me->name() + 
//                        "ȡ���˺��������ͷ��\n" NOR);
                 me->set("marks/"+obj->name(1), 1);
           tell_object(obj, MAG "�����Ը��ͶԷ���Ϊ�򸾣�����Ҳ��" 
                        +me->name() + "("+(string)me->query("id")+
                        ")"+ "��һ�� marry ָ�\n" NOR);
                write(MAG  
                        "�����㼱�����������������˵ͬ��...\n" NOR);
                return 1;
        }
        

        marry_card1 = new("/obj/marry_card");
        marry_card1->set("name","���"+obj->query("id")+"�Ļ�Լ");
        marry_card1->move(me);
        marry_card2 = new("/obj/marry_card");
        marry_card2->set("name","���"+me->query("id")+"�Ļ�Լ");
        marry_card2->move(obj);
        
        message_vision(MAG "��ϲ $N �� $n ��һ�����ϲ����Ե��\n" NOR,
        obj, me);
//        message("chat", me->name() + "��" + obj->name() + 
//        "���ڿ�ʼ�Ƿ���\n", environment(me),me); 
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s �� %s ���ڿ�ʼ�Ƿ���! \n", 
        me->name(1), obj->name(1)));


        return 1;
}

int do_unmarry(string arg)
{
        object marry_card1,marry_card2,  me;
        object *list,ob, couple_ob;
        int i, have_marry;
        string target, tmpstr1, tmpstr2,str1,str2;
        string cardname;
             
        me = this_player();       
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
              if (((string)list[i]->query("id")) == "marrycard") {
                        marry_card1 = list[i];                     
                        cardname = list[i]->query("name");
                        have_marry = 1;
                }
        }

        if (have_marry == 0)
                return notify_fail("�㻹δ�л�Լ����\n");
        if( !environment()
        ||      base_name(environment()) != query("startroom") )
           return notify_fail("���Ǳ�Ǹ��������һ�µ�����ׯ�����Ұɡ�\n");
        if (sscanf(cardname,"���%s�Ļ�Լ" ,target)!=1)
                return notify_fail("��û�а���.\n");

         if(!objectp(couple_ob = present(target, environment(me)))
                || !find_player(target) )
                return notify_fail("��İ������ڲ��ڳ�.\n");

        if ((string)couple_ob->query("gender") != "Ů��") {
                tmpstr1 = "����"; tmpstr2 = "�Ϲ�";
                str1 = "��"; str2 = "��";
        } else {
                tmpstr1 = "�Ϲ�"; tmpstr2 = "����";
                str1 = "��"; str2 = "��";
        }

        list = all_inventory(couple_ob);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
              if (((string)list[i]->query("id")) == "marrycard") {
                        marry_card2 = list[i];                     
                        have_marry = 1;
                }
        }
        if (have_marry = 0) {
                destruct(marry_card1);                  
        message_vision(MAG " $N �� $n �����ڿ�ʼ�����Լ,�������!\n" NOR,
        couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s �� %s �����ڿ�ʼ�����Լ,�������! \n",
        me->name(1), couple_ob->name(1)));

                return 1;

        }

        if( userp(couple_ob) && !((object)couple_ob->query("marks/"
                + "unmarry" +me->name(1))) ) {
                message_vision(MAG "\n$N����$n˵����" 
                        + RANK_D->query_self(me) 
                        + me->name() + "�����ǽ����Լ��!����?\n\n"
                        NOR, me, couple_ob);           
                 me->set("marks/"+"unmarry"+couple_ob->name(1), 1);
           tell_object(couple_ob, MAG "�����Ը������Լ������Ҳ"
                + "��һ�� unmarry ָ�\n" NOR);
                write(MAG  
                "������ֻ�е���" +str2 +" ͬ����...\n" NOR);
                return 1;
        }

        destruct(marry_card1);
        destruct(marry_card2);
        
        message_vision(MAG " $N �� $n �����ڿ�ʼ�����Լ,�������!\n" NOR,
        couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s �� %s �����ڿ�ʼ�����Լ,�������! \n", 
        me->name(1), couple_ob->name(1)));

        return 1;
}