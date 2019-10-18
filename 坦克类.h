#include<iostream>
#include<string>
#include<Windows.h>
#include<ctime>
#include<cstdlib>

using namespace std;

#define true 1
#define error 0
#define fault -1
#define height 30
#define width 30
#define mix 30

enum direction { u, d, l, r };//̹�˷���

clock_t start, end;//��ʱ

int ran;//���������
int fraction =0 ;//�Ʒ�



typedef struct position {
	int x;//�����꣬����һ��λ��
	int y;//�����꣬һ��һ��λ��
	bool operator==(position b) {//�����ж������Ƿ񿿽����ӵ��жϣ���������true������������false
		int d;
		d = (this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y);
		if (d < 2)return true;
		return false;
	}

}point;
//����ϵ����

bool contrast(point a, point b) {//�ж��������Ƿ���ȣ�a�ϴ󷵻�false��a��С����true����Ƚ��д�ӡ
	if (a.x < b.x)
	{
		return true;
	}
	else if (a.x == b.x)
	{
		if (a.y < b.y)
		{
			return true;
		}
		else if (a.y > b.y)
		{
			return false;
		}
		else
		{
			cout << "���������" << endl;
		}
	}
	else
	{
		return false;
	}

}
//�ж��������Ƿ���ȣ�a�ϴ󷵻�false��a��С����true����Ƚ��д�ӡ


bool the_wall(point p) {//�жϸõ��Ƿ�ײǽ��ײǽ����false��û���򷵻�true
	if (p.x<1 || p.x > width - 1 || p.y <1 || p.y >height - 1)
	{
		return false;
	}
	return true;
}
//�жϸõ��Ƿ�ײǽ��ײǽ����false��û���򷵻�true

void startgame();//��Ϸ��ʼ����
void initgame();//��ʼ����Ϸ
void endgame();//��Ϸ����

void pointdefine(point& t, int i = 1) {//Ĭ�϶�λ��������
	switch (i)
	{
	case -1:
		t.x = -1;
		t.y = -1;
		break;

	case 0:
		t.x = width / 2;
		t.y = height - 1;
		break;

	case 1:
		t.x = 1;
		t.y = 1;
		break;

	case 2:
		t.x = width / 3;
		t.y = 1;
		break;

	case 3:
		t.x = width - width / 3;
		t.y = 1;
		break;

	case 4:
		t.x = width - 1;
		t.y = 1;
		break;

	default:
		t.x = width / 2;
		t.y = height / 2;
		break;
	}
}
//Ĭ�϶�λ��������

void  gotoxy(point p) {//��λ���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int x = 2 * p.x;
	pos.X = x;
	pos.Y = p.y;
	SetConsoleCursorPosition(handle, pos);
}
//��λ���


class tank {//̹�˵��ຯ��
private:
	int t_numble;//���
	int t_live;//̹������
	int t_speed;//̹���ٶ�
	bool order;//������
protected:
	int t_power;//̹�˹�����
	point t_po;//̹����������
	direction t_direction;//̹�˵ķ���

public:
	tank() {}//�չ��캯����������ת��

	tank(point point, int numble = -1, int live = 3, int speed = 1, int power = 1, direction direction1 = u) {//��ʼ��̹�˵�����
		t_numble = numble;
		t_live = live;
		t_speed = speed;
		t_power = power;
		t_po = point;
		t_direction = direction1;
	}
	//���ع��캯����Ĭ��Ϊ���̹��ǿ��

	void get_numble(int& t) {//�����ʾ
		t = t_numble;
	}
	//�����ʾ

	void get_live(int& l) {//����ֵ��ʾ
		l = t_live;
	}
	//����ֵ��ʾ

	void get_speed(int& s) {//�ٶ���ʾ
		s = t_speed;
	}
	//�ٶ���ʾ

	void get_power(int& p) {//��������ʾ
		p = t_power;
	}
	//��������ʾ

	void get_t_po(point& p) {//������ʾ
		p = t_po;
	}
	//������ʾ

	void get_t_direction(direction& d) {//�����ȡ
		d = t_direction;
	}
	//������ʾ

	void c_live(int live = 1) {//����ֵ�ı�
		t_live += live;
	}
	//����ֵ�ı䣬Ĭ��Ϊ��һ

	void c_speed(int speed = 1) {
		t_speed += speed;
	}
	//�ٶȸı䣬Ĭ��Ϊ��һ

	void c_power(int power = 1) {//�������ı�
		t_power += power;
	}
	//�������ı䣬Ĭ��Ϊ��һ

	void c_po(point p) {//����ı�
		t_po = p;
	}
	//����ı�

	void c_direction(direction direction1) {//����仯
		t_direction = direction1;
	}
	//����仯

	bool get_order() {//��ȡ������
		return order;
	}
	//��ȡ������

	void c_order() {//�ı�������
		order = true;
	}
	//�ı�������

	void root_order() {//����������
		order = false;
	}
	//����������

	void print_tank() {//̹�˴�ӡ
		point p2 = t_po;
		p2.x--;
		switch (t_direction)
		{
		case u:
			gotoxy(p2);
			cout << "�����";//������
			p2.y--;
			gotoxy(p2);
			cout << "  �� ";
			p2.y += 2;
			gotoxy(p2);
			cout << "��  ��";
			break;
		case d:
			gotoxy(p2);
			cout << "�����";//������
			p2.y++;
			gotoxy(p2);
			cout << "  �� ";
			p2.y -= 2;
			gotoxy(p2);
			cout << "��  ��";
			break;
		case l:
			gotoxy(p2);
			cout << "���� ";
			p2.y--;
			gotoxy(p2);
			cout << "  ����";
			p2.y += 2;
			gotoxy(p2);
			cout << "  ����";
			break;
		case r:
			gotoxy(p2);
			cout << "  ���";
			p2.y--;
			gotoxy(p2);
			cout << "����  ";
			p2.y += 2;
			gotoxy(p2);
			cout << "����  ";
			break;

		default:
			break;
		}
	}
	//̹�˴�ӡ

	void move() {//ֱ��λ�ƣ������ǵ�������������н���������
		switch (t_direction)
		{
		case u:
			t_po.y--;
			break;
		case d:
			t_po.y++;
			break;
		case l:
			t_po.x--;
			break;
		case r:
			t_po.x++;
		default:
			break;
		}
	}
	//ֱ��λ�ƣ������ǵ�������������н������Կɿ��Դ���
};
//̹���ຯ��

class  bullet {//�ӵ��ຯ��
private:
	direction t_direction;//�ӵ�����
	point t_po;//�ӵ�����
	int t_power;//�ӵ�����

public:
	bullet() {};
	//�ӵ��Ŀչ��캯�������ڴ����ޱ���

	bullet(int power, direction d, point p) {//�ӵ������������캯��
		t_po = p;
		t_direction = d;
		t_power = power;
	}
	//�ӵ������������캯��

	bullet(tank t) {//�ӵ���̹��ֱ�ӷ����Ĺ��캯��
		t.get_t_po(t_po);
		t.get_t_direction(t_direction);
		t.get_power(t_power);
		switch (t_direction)//λ��һ������ֱ���ж��ӵ�����
		{
		case u:
			t_po.y -= 2;
			break;
		case d:
			t_po.y += 2;
			break;
		case l:
			t_po.x -= 2;
			break;
		case r:
			t_po.x += 2;
		default:
			break;
		}

	}
	/*�ӵ���̹��ֱ�ӷ����Ĺ��캯��
	�Ҹ��ݷ���λ�����������ֱ���ж��ӵ�����*/

	bullet& operator=(tank t) {//���ظ�ֵ�ţ�����ֱ����̹������и�ֵ
		t.get_t_direction(this->t_direction);
		t.get_t_po(this->t_po);
		t.get_power(this->t_power);
		return *this;//�м�һ��Ҫ����this�����򽫻ᱨ��
		switch (t_direction)//λ��һ������ֱ���ж��ӵ�����
		{
		case u:
			t_po.y--;
			break;
		case d:
			t_po.y++;
			break;
		case l:
			t_po.x--;
			break;
		case r:
			t_po.x++;
		default:
			break;
		}
	}
	/*���ظ�ֵ�ţ�����ֱ����̹������и�ֵ
	�Ҹ��ݷ���λ��һ������ֱ���ж��ӵ�����*/

	void get_p(point& p) {//��ȡ����
		p = t_po;
	}
	//��ȡ����

	void get_dir(direction& dir) {//��ȡ����
		dir = t_direction;
	}
	//��ȡ����

	void get_power(int& power) {//��ȡ����
		power = t_power;
	}
	//��ȡ����

	void c_p(point p) {//��������
		t_po = p;
	}
	//��������

	void print_b() {//��ӡ�ӵ�
		gotoxy(t_po);
		cout << "*";
	}
	//��ӡ�ӵ�

	void move() {//ֱ��λ�ƣ������ǵ�������������н���������
		switch (t_direction)
		{
		case u:
			t_po.y--;
			break;
		case d:
			t_po.y++;
			break;
		case l:
			t_po.x--;
			break;
		case r:
			t_po.x++;
		default:
			break;
		}
	}
	//ֱ��λ�ƣ������ǵ�������������н������Կɿ��Դ���
};
//�ӵ��ຯ��

typedef struct tank_node//̹������ڵ�
{
	tank data;
	tank_node* next;
	tank_node* prev;
}tank_node;
//̹������ڵ�

typedef struct tank_list {//̹������
	tank_node* head;
	int size;
}tank_list;
//̹��������ʵֱ������Ҳ�У�ֻ��������Ϊֱ��

typedef struct bb {//�ӵ�����
	bullet data;
	bb* next;
	bb* prev;
}bb;
//�ӵ�����ڵ�

typedef struct blist {
	bb* head;
}blist;
//�ӵ�����̹ͬ������

class tanklist {//̹��������ɾ�Ĳ�
private:
	tank_list t;
	blist  bt;
public:
	tanklist() {//Ĭ�Ϲ��캯��
		t.head = (tank_node*)malloc(sizeof(tank_node));
		if (!t.head) {//�ж�ͷ����Ƿ񴴽��ɹ�
			cout << "ͷ���" << endl;
			while (1) {
				if (cin.get() != 'y')
				{
					exit(0);
				}
			}
		}

		t.size = 0;
		point p;
		pointdefine(p, 0);//Ĭ����ҵ�λ
		t.head->data = tank(p);//ͷ��㴢�������Ϣ
		t.head->prev = NULL;//ǰΪ��
		t.head->next = NULL;//��Ϊ�գ������жϺ����Ƿ��нڵ�


		bt.head = (bb*)malloc(sizeof(bb));//�ӵ�ͷ���
		if (!bt.head) {
			cout << "ͷ���" << endl;
			while (1) {
				if (cin.get() != 'y')
				{
					exit(0);
				}
			}
		}
		bt.head->next = NULL;
		bt.head->prev = NULL;
		//ǰΪ����ӵ�����Ϊ�����ӵ�
	}
	//Ĭ�Ϲ��캯���������������

	~tanklist() {//����������ɾ����������
		deleteall();
	}
	//����������ɾ���������ݣ�����������

	void deleteall() {//ɾ���������ݣ��ͷſռ䣬������ֿռ�һֱ��ռ��
		tank_node* t1, * t2;
		t1 = t.head->next;
		while (t1 != NULL)//��ͷ������һ����ʼ�ͷ�
		{
			t2 = t1->next;//�ȱ���ָ����һλ��ָ�룬��ֹ�ռ��ͷź��Ҳ�����һƬ�ڴ��ַ
			free(t1);
			t1 = t2;
		}
		free(t.head);

		bb* b1, * b2;
		b1 = bt.head->next;
		while (b1 != NULL) {//�����ͷţ��ұ���ͷ���
			b2 = b1->next;
			free(b1);
			b1 = b2;
		}
		b1 = bt.head->prev;//��ǰ
		while (b1 != NULL)
		{
			b2 = b1->prev;
			free(b1);
			b1 = b2;
		}
		free(bt.head);//����ͷ�ͷ���
	}
	//ɾ���������ݣ��ͷſռ䣬������ֿռ�һֱ��ռ��

	//��ɾ�Ĳ�
	//��

	void tank_add(const point p, int live = 3, int speed = 1, int power = 1, direction direction1 = u) {//���ӽڵ�
		tank_node* tnode1 = t.head->next;
		tank_node* tnode2 = NULL;
		tank t0(p, t.size, live, speed, power, direction1);
		point p0;
		tnode2 = (tank_node*)malloc(sizeof(tank_node));
		if (!tnode2)
		{
			cout << "��ӽڵ�" << endl;
			cout << "��y�˳�" << endl;
			while (1) {
				if (cin.get() == 'y')
				{
					exit(0);
				}
			}
		}

		tnode2->data = t0;
		tnode2->data.root_order();

		while (tnode1 != NULL) {//�����жϣ����ڵ��С������룬���ж�x�����ж�y
			tnode1->data.get_t_po(p0);//��ȡ�ڵ�����p0
			if (contrast(p0, p)) {//�������true������p0��С���ɼ��������жϣ���ʱ�������
				if (tnode1->next == NULL)//����Ѿ��������һλ,ֱ���˳�ѭ������tnode1������λ��
				{
					break;
				}
				tnode1 = tnode1->next;
				continue;
			}
			else
			{//�������false����ʾ�Ѿ�����λ�ã���ǰ����һ�񣬲��������
				tnode1 = tnode1->prev;
				tnode2->next = tnode1->next;
				tnode2->prev = tnode1;
				tnode1->next = tnode2;
				tnode2->next->prev = tnode2;
				t.size++;
				break;
			}

		}
		if (t.head->next == NULL)//���ͷ����û�����ݣ�ֱ�Ӳ��뵽ͷ����
		{
			tnode2->next = t.head->next;
			tnode2->prev = t.head;
			t.head->next = tnode2;
			t.size++;
		}
		if ((tnode1 != NULL) && (tnode1->next == NULL))//���tnode1�ǿ���tnode1����Ϊ�գ���ʾ�Ѿ�ѭ�������һλ
		{
			tnode2->next = tnode1->next;
			tnode2->prev = tnode1;
			tnode1->next = tnode2;
			t.size++;
		}

	}
	//���ӽڵ㣬�ҽڵ��С��С��������

	void bb_add(const tank_node* tb, bool player = false) {//�����ӵ��ڵ�
		bb* bnode;
		bullet bbt(tb->data);
		bnode = (bb*)malloc(sizeof(bb));
		if (!bnode)
		{
			cout << "����ӵ��ڵ�" << endl;
			while (1) {
				if (cin.get() != 'y')
				{
					exit(0);
				}
			}
		}
		bnode->data = bbt;
		//�����ڵ㣬Ȼ�����������

		switch (player)//player�����ж��Ƿ�Ϊ����ӵ�����ֱ�Ӳ��뵽ͷ���ǰ��
		{
		case true:

			bnode->prev = bt.head->prev;
			bnode->next = bt.head;
			bt.head->prev = bnode;
			if (bnode->prev != NULL)
			{
				bnode->prev->next = bnode;
			}
			break;

		case false:
			bnode->prev = bt.head;
			bnode->next = bt.head->next;
			bt.head->next = bnode;
			if (bnode->next != NULL)
			{
				bnode->next->prev = bnode;
			}
			break;
		}
	}
	//�����ӵ��ڵ�,playerΪfalse��Ϊ�����ӵ�

	//ɾ

	void tank_delete(tank_node*& tnode) {//����ָ��ɾ���ڵ�

		if (tnode->next == NULL)
		{
			tnode->prev->next = NULL;
			free(tnode);
			fraction++;
			t.size--;
		}
		else
		{
			tnode->prev->next = tnode->next;
			tnode->next->prev = tnode->prev;
			free(tnode);
			fraction ++;
			t.size--;
		}
		tnode = NULL;
	}
	//����ָ��ɾ��tank�ڵ�

	void bb_delete(bb*& bnode) {//����ָ��ɾ���ӵ��ڵ�
		if (bnode->next != NULL) {
			bnode->next->prev = bnode->prev;
		}
		if (bnode->prev != NULL) {
			bnode->prev->next = bnode->next;
		}
		if (bnode != NULL) {
			free(bnode);
			bnode = NULL;
		}
	}
	//����ָ��ɾ���ӵ��ڵ�

	//�ģ��ƶ�
	//��д�жϺ���

	bool distance_calculate_tank_ai(tank_node* tp) {//�����tank������룬���������򷵻�true
		point a, b;
		tp->data.get_t_po(a);
		tank_node* t0;
		t0 = tp->prev;
		while (!(t0 == t.head)) {//��ǰһֱ��ͷ������һ��
			t0->data.get_t_po(b);
			t0 = t0->prev;
			if ((a.x - b.x) * (a.x - b.x) < 9) {//����x�������С��3�����ж�y����������������
				if ((a.y - b.y) * (a.y - b.y) < 9) {//���y�Ĳ�ҲС��3������false��
					return false;
				}
				else {
					continue;
				}
			}
			else
			{
				break;
			}
		}
		t0 = tp->next;
		while (t0 != NULL)//����һֱ�����
		{
			t0->data.get_t_po(b);
			t0 = t0->next;
			if ((a.x - b.x) * (a.x - b.x) < 9)
			{
				if ((a.y - b.y) * (a.y - b.y) < 9)
				{
					return false;
				}
				else
				{
					continue;
				}
			}
			else
			{
				break;
			}
		}
		t.head->data.get_t_po(b);
		if ((a.x - b.x) * (a.x - b.x) < 9)//����ж�����ҵľ���
		{
			if ((a.y - b.y) * (a.y - b.y) < 9)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	//�����tank֮���໥������룬���������򷵻�true

	bool distance_calculate_player() {//���̹�˾�����㣬���������򷵻�true
		tank_node* tnode = t.head->next;
		point player, p;
		t.head->data.get_t_po(player);
		while (tnode != NULL) {//ѭ��������x��С����
			tnode->data.get_t_po(p);
			tnode = tnode->next;
			if ((p.x - player.x) * (p.x - player.x) < 9)
			{
				if ((p.y - player.y) * (p.x - player.y) < 9)
				{
					return false;
				}
				else
				{
					continue;
				}
			}
			else if ((p.x - player.x) > 3)//����ýڵ��x��player.x��3�������һ����3��ֱ�ӷ���true
			{
				return true;
			}
			else
			{
				continue;
			}
		}
		return true;//��ѭ����������û�з���false�����ʾ������
	}
	//���̹��������̹�˵ľ�����㣬���������򷵻�true

	bool tank_move_judge(tank_node* tnode, bool flag) {//�жϺ����������ж�̹��λ���Ƿ��ܳɹ�
		point p;
		tnode->data.get_t_po(p);
		int a, b;
		a = the_wall(p);
		if (flag)
		{
			b = distance_calculate_player();
		}
		else
		{
			b = distance_calculate_tank_ai(tnode);
		}
		return a && b;
	}
	//�жϺ����������ж�̹��λ���Ƿ��ܳɹ���flag����ȷ������һ���ai

	void tank_move(tank_node* tnode, direction dir = u, bool flag = false) {//̹���ƶ�����
		point p;
		int speed;
		if (!flag)
		{
			tnode->data.get_t_direction(dir);
		}
		tnode->data.get_t_po(p);
		tnode->data.get_speed(speed);
		switch (dir) {
		case u:
			for (int i = 0; i < speed; i++) {
				p.y--;
				tnode->data.c_po(p);
				if (!tank_move_judge(tnode, flag)) {
					p.y++;
					tnode->data.c_po(p);
					break;
				}
			}
			break;
		case d:
			for (int i = 0; i < speed; i++) {
				p.y++;
				tnode->data.c_po(p);
				if (!tank_move_judge(tnode, flag)) {
					p.y--;
					tnode->data.c_po(p);
					break;
				}
			}
			break;
		case l:
			for (int i = 0; i < speed; i++) {
				p.x--;
				tnode->data.c_po(p);
				if (!tank_move_judge(tnode, flag)) {
					p.x++;
					tnode->data.c_po(p);
					break;
				}
			}
			break;
		case r:
			for (int i = 0; i < speed; i++) {
				p.x++;
				tnode->data.c_po(p);
				if (!tank_move_judge(tnode, flag)) {
					p.x--;
					tnode->data.c_po(p);
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	//̹���ƶ�����

	void tank_do(tank_node* tnode) {//����̹���ж�
		direction dir;
		srand(ran);
		ran = rand();
		dir = (direction)(ran % 4);
		unsigned int random;
		random = ran;
		srand(ran);//�������ӣ�������ָ��ʲ���
		ran = rand();
		if ((ran % 4) == 1)
		{
			tnode->data.c_direction(dir);
		}
		srand(ran);
		ran = rand();
		if ((ran % 2) == 1)//����֮һ�����ƶ�
		{
			tank_move(tnode);
		}
		srand(ran);
		ran = rand();
		if ((ran % 7) == 1)//�߷�֮һ���ʹ���
		{
			bb_add(tnode, false);
		}
	}
	//����̹���ж���ת���ƶ�������

	void tank_do_all() {//ȫ��̹���ж�
		tank_node* tnode = t.head->next;
		while (tnode != NULL)
		{
			tank_do(tnode);
			if (order()) {
				tnode = tnode->next;
			}
			else
			{
				endgame();
			}

		}
	}
	//ȫ��̹���ж�,����ֱ�ӵ��ã����Ե�����

	void bb_move(bb* bnode) {//�ӵ��ƶ�����
		direction dir;
		point p;
		bnode->data.get_dir(dir);
		bnode->data.get_p(p);
		switch (dir) {
		case u:
			p.y--;
			bnode->data.c_p(p);
			break;
		case d:
			p.y++;
			bnode->data.c_p(p);
			break;
		case l:
			p.x--;
			bnode->data.c_p(p);
			break;
		case r:
			p.x++;
			bnode->data.c_p(p);
			break;
		default:
			break;
		}
	}
	//�ӵ��ƶ�����

	void bb_move_all() {//ȫ���ӵ��ƶ�����
		bb* bnode = bt.head->next;
		while (bnode != NULL)
		{
			bb_move(bnode);
			bnode = bnode->next;
		}
		bnode = bt.head->prev;
		while (bnode != NULL)
		{
			bb_move(bnode);
			bnode = bnode->prev;
		}
	}
	//ȫ���ӵ��ƶ�����

	void player_tank_move(direction dir) {//���̹���ƶ�
		t.head->data.c_direction(dir);
		tank_move(t.head, dir, true);
	}
	//���̹���ƶ�

	void player_attack() {//���̹�˹���
		bb_add(t.head, true);
	}
	//���̹�˹���

	void move_all() {//���е�λ�����˶�
		bb_move_all();
		tank_do_all();
	}
	//���е�λ�����˶�

	//��

	void get_size(int& s) {	//�����Ĵ�С
		s = t.size;
	}
	//�����Ĵ�С

	void get_tank( point& p, int& live, int& power, int& speed, direction& direction1, tank_node* tnode = NULL) {//��ȡ̹����Ϣ
		if (tnode == NULL)
		{
			 tnode=t.head;
		}
		tnode->data.get_t_po(p);
		tnode->data.get_live(live);
		tnode->data.get_power(power);
		tnode->data.get_speed(speed);
		tnode->data.get_t_direction(direction1);
	}
	//��ȡ̹����Ϣ

	//����

	bool order() {//���������
		order_tank();
		tank_node* tnode = t.head->next;
		while (tnode != NULL)
		{
			if (!tnode->data.get_order())
			{
				return false;
			}
			tnode = tnode->next;
		}
		root_order();
		return true;
	}
	//���������

	void root_order() {//�����ǹ���
		tank_node* tnode = t.head->next;
		while (tnode != NULL)
		{
			tnode->data.root_order();
			tnode = tnode->next;
		}
	}
	//�����ǹ���

	void order_tank() {//����
		tank_node* t2 = t.head->next;
		tank_node* t1;
		tank_node* tnode;
		point a, b, c;
		while (t2->next != NULL)//ѭ����β��ǰһ��
		{
			t1 = t2->next;//˳��Ϊhead��������t2��t1������
			t2->data.get_t_po(a);
			t1->data.get_t_po(b);
			if (contrast(a, b))//����aС��b���������ƣ��Ҹ���t2�ı��
			{
				t2->data.c_order();
				t2 = t1;
			}
			else//����a����b����ʾb��С��t1��Ҫǰ��
			{
				tnode = t2->prev;
				tnode->data.get_t_po(c);
				while ((!contrast(c, b)) && (tnode != t.head))//һֱǰ�Ƶ�cС��b���ߣ�tnodeΪͷ��㣬ͣ��
				{
					tnode = tnode->prev;
					tnode->data.get_t_po(c);
				}
				t2->next = t1->next;
				t1->next = tnode->next;
				t1->next->prev = t1;
				t1->prev = tnode;
				tnode->next = t1;
				t1->data.c_order();
				if (t2->next != NULL)
				{
					t2->next->prev = t2;
				}
			}


		}
		if (t2->next == NULL)
		{
			t2->data.c_order();
		}
	}
	//̹������

	//����

	int distance_calculate_bb_and_tank(tank_node* tnode = NULL, bool flag = true) {//����ӵ��뵥��̹�˵Ľ�����Ȼ�����ɾ��
		bb* bnode = bt.head;
		bb* kill;
		point b, p;
		int power;
		if (flag)
		{
			t.head->data.get_t_po(p);
			bnode = bt.head->prev;
			while (bnode != NULL)//�Ƚ�����뼺���ӵ������жϣ��������Ӵ����ӵ�
			{
				kill = bnode;
				bnode = bnode->prev;
				kill->data.get_p(b);
				if (b == p)
				{
					bb_delete(kill);
				}
			}
			//�����ai�ӵ�
			bnode = bt.head->next;
			while (bnode != NULL)
			{
				bnode->data.get_p(b);
				if (b == p)
				{
					bnode->data.get_power(power);
					bb_delete(bnode);
					return power;
				}
				bnode = bnode->next;
			}
			return 0;
		}
		else
		{
			tnode->data.get_t_po(p);
			bnode = bt.head->next;
			while (bnode != NULL)//�Ƚ�ai��ai�ӵ������жϣ��������Ӵ����ӵ�
			{
				kill = bnode;
				bnode = bnode->next;
				kill->data.get_p(b);
				if (b == p)
				{
					bb_delete(kill);
				}
			}
			//ai������ӵ�����
			bnode = bt.head->prev;
			while (bnode != NULL)
			{
				bnode->data.get_p(b);
				if (b == p)
				{
					bnode->data.get_power(power);
					bb_delete(bnode);
					return power;
				}
				bnode = bnode->prev;
			}
			return 0;
		}
	}
	//���̹�˽ڵ����ӵ��Ľ�����Ȼ�����ɾ�� ��Ĭ��Ϊ�����з��ӵ�,����ֵΪ�ӵ�����

	void hit_tank() {//���Ӵ���̹�˵��ӵ�������������������̹���˺�
		tank_node* tnode = t.head->next;
		int hit = distance_calculate_bb_and_tank();
		t.head->data.c_live(-hit);
		while (tnode != NULL)
		{
			hit = distance_calculate_bb_and_tank(tnode, false);
			tnode->data.c_live(-hit);
			tnode = tnode->next;
		}
	}
	//���Ӵ���̹�˵��ӵ�������������������̹���˺�

	void tank_kill() {//������ֵ����1��̹��ɾ����������������㽫������Ϸ
		tank_node* tnode = t.head->next;
		tank_node* kill;
		int live;
		t.head->data.get_live(live);
		if (live <= 0)
		{
			endgame();
		}
		while (tnode != NULL)
		{
			kill = tnode;
			tnode = tnode->next;
			kill->data.get_live(live);
			if (live <= 0)
			{
				tank_delete(kill);
			}
		}
	}
	//������ֵ����1��̹��ɾ��

	void bb_kill() {//��ǽ���ӵ�ɾ��
		bb* bnode = bt.head->next;
		bb* kill;
		point p;
		while (bnode != NULL)
		{
			kill = bnode;
			bnode = bnode->next;
			kill->data.get_p(p);
			if (!the_wall(p))
			{
				bb_delete(kill);
			}
		}
		bnode = bt.head->prev;
		while (bnode != NULL)
		{
			kill = bnode;
			bnode = bnode->prev;
			kill->data.get_p(p);
			if (!the_wall(p))
			{
				bb_delete(kill);
			}
		}
	}
	//��ǽ���ӵ�ɾ��

	void kill() {//��������������������ɾ��ǽ���ӵ���Ȼ��̹���ӵ���������ɾ��̹��
		bb_kill();
		hit_tank();
		tank_kill();
	}
	//��������������������ɾ��ǽ���ӵ���Ȼ��̹���ӵ���������ɾ��̹��,ֱ�ӵ��øú���

	void print_all() {//��ӡ���е�λ
		system("cls");
		tank_node* tnode = t.head;
		bb* bnode;
		while (tnode != NULL)
		{
			tnode->data.print_tank();
			tnode = tnode->next;
		}
		bnode = bt.head->next;
		while (bnode != NULL)
		{
			bnode->data.print_b();
			bnode = bnode->next;
		}
		bnode = bt.head->prev;
		while (bnode != NULL)
		{
			bnode->data.print_b();
			bnode = bnode->prev;
		}
	}
	//��ӡ���е�λ
};
