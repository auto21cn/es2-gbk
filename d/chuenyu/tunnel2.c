inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����ںڰ������������ֲ�����ָ��Ψһ�Ĺ�������ǽ�Ϻ���������
���͵ơ����Ϻ�ǽ�ϲ����˰���ɫ��Ѫ�ۣ�ɢ�����������������ϴ�����
�������������ĵ�����ص�������ë����Ȼ��
LONG
                );
                set("exits", ([ /* sizeof() == 3 */
                "east" : __DIR__"tunnel6",
                  "north" : __DIR__"tunnel3",
                    "south"   : __DIR__"tunnel1",
                    ]));
                    
        setup();
        replace_program(ROOM);
                   
}
                    