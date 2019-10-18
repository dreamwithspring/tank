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

enum direction { u, d, l, r };//坦克方向

clock_t start, end;//计时

int ran;//随机数做种
int fraction =0 ;//计分



typedef struct position {
	int x;//横坐标，两格一个位置
	int y;//纵坐标，一格一格位置
	bool operator==(position b) {//用于判断两点是否靠近，子弹判断，靠近返回true，不靠近返回false
		int d;
		d = (this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y);
		if (d < 2)return true;
		return false;
	}

}point;
//坐标系构成

bool contrast(point a, point b) {//判断两坐标是否相等，a较大返回false，a较小返回true，相等进行打印
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
			cout << "两坐标相等" << endl;
		}
	}
	else
	{
		return false;
	}

}
//判断两坐标是否相等，a较大返回false，a较小返回true，相等进行打印


bool the_wall(point p) {//判断该点是否撞墙，撞墙返回false，没有则返回true
	if (p.x<1 || p.x > width - 1 || p.y <1 || p.y >height - 1)
	{
		return false;
	}
	return true;
}
//判断该点是否撞墙，撞墙返回false，没有则返回true

void startgame();//游戏开始界面
void initgame();//初始化游戏
void endgame();//游戏结束

void pointdefine(point& t, int i = 1) {//默认定位函数整合
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
//默认定位函数整合

void  gotoxy(point p) {//定位光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int x = 2 * p.x;
	pos.X = x;
	pos.Y = p.y;
	SetConsoleCursorPosition(handle, pos);
}
//定位光标


class tank {//坦克的类函数
private:
	int t_numble;//标号
	int t_live;//坦克生命
	int t_speed;//坦克速度
	bool order;//排序标记
protected:
	int t_power;//坦克攻击力
	point t_po;//坦克中心坐标
	direction t_direction;//坦克的方向

public:
	tank() {}//空构造函数用于数据转移

	tank(point point, int numble = -1, int live = 3, int speed = 1, int power = 1, direction direction1 = u) {//初始化坦克的属性
		t_numble = numble;
		t_live = live;
		t_speed = speed;
		t_power = power;
		t_po = point;
		t_direction = direction1;
	}
	//重载构造函数，默认为玩家坦克强度

	void get_numble(int& t) {//标号显示
		t = t_numble;
	}
	//标号显示

	void get_live(int& l) {//生命值显示
		l = t_live;
	}
	//生命值显示

	void get_speed(int& s) {//速度显示
		s = t_speed;
	}
	//速度显示

	void get_power(int& p) {//攻击力显示
		p = t_power;
	}
	//攻击力显示

	void get_t_po(point& p) {//坐标显示
		p = t_po;
	}
	//坐标显示

	void get_t_direction(direction& d) {//方向获取
		d = t_direction;
	}
	//方向显示

	void c_live(int live = 1) {//生命值改变
		t_live += live;
	}
	//生命值改变，默认为加一

	void c_speed(int speed = 1) {
		t_speed += speed;
	}
	//速度改变，默认为加一

	void c_power(int power = 1) {//攻击力改变
		t_power += power;
	}
	//攻击力改变，默认为加一

	void c_po(point p) {//坐标改变
		t_po = p;
	}
	//坐标改变

	void c_direction(direction direction1) {//方向变化
		t_direction = direction1;
	}
	//方向变化

	bool get_order() {//获取秩序标记
		return order;
	}
	//获取秩序标记

	void c_order() {//改变秩序标记
		order = true;
	}
	//改变秩序标记

	void root_order() {//归零秩序标记
		order = false;
	}
	//归零秩序标记

	void print_tank() {//坦克打印
		point p2 = t_po;
		p2.x--;
		switch (t_direction)
		{
		case u:
			gotoxy(p2);
			cout << "■☆■";//☆■☆■
			p2.y--;
			gotoxy(p2);
			cout << "  ■ ";
			p2.y += 2;
			gotoxy(p2);
			cout << "■  ■";
			break;
		case d:
			gotoxy(p2);
			cout << "■☆■";//☆■☆■
			p2.y++;
			gotoxy(p2);
			cout << "  ■ ";
			p2.y -= 2;
			gotoxy(p2);
			cout << "■  ■";
			break;
		case l:
			gotoxy(p2);
			cout << "■☆ ";
			p2.y--;
			gotoxy(p2);
			cout << "  ■■";
			p2.y += 2;
			gotoxy(p2);
			cout << "  ■■";
			break;
		case r:
			gotoxy(p2);
			cout << "  ☆■";
			p2.y--;
			gotoxy(p2);
			cout << "■■  ";
			p2.y += 2;
			gotoxy(p2);
			cout << "■■  ";
			break;

		default:
			break;
		}
	}
	//坦克打印

	void move() {//直接位移，但考虑到与其他对象进行交互，存疑
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
	//直接位移，但考虑到与其他对象进行交互，对可靠性存疑
};
//坦克类函数

class  bullet {//子弹类函数
private:
	direction t_direction;//子弹方向
	point t_po;//子弹坐标
	int t_power;//子弹威力

public:
	bullet() {};
	//子弹的空构造函数，用于创建无变量

	bullet(int power, direction d, point p) {//子弹的三变量构造函数
		t_po = p;
		t_direction = d;
		t_power = power;
	}
	//子弹的三变量构造函数

	bullet(tank t) {//子弹由坦克直接发出的构造函数
		t.get_t_po(t_po);
		t.get_t_direction(t_direction);
		t.get_power(t_power);
		switch (t_direction)//位移一格，以免直接判断子弹销毁
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
	/*子弹由坦克直接发出的构造函数
	且根据方向位移两格格，以免直接判断子弹销毁*/

	bullet& operator=(tank t) {//重载赋值号，方便直接由坦克类进行赋值
		t.get_t_direction(this->t_direction);
		t.get_t_po(this->t_po);
		t.get_power(this->t_power);
		return *this;//切记一定要返回this，否则将会报错
		switch (t_direction)//位移一格，以免直接判断子弹销毁
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
	/*重载赋值号，方便直接由坦克类进行赋值
	且根据方向位移一格，以免直接判断子弹销毁*/

	void get_p(point& p) {//获取坐标
		p = t_po;
	}
	//获取坐标

	void get_dir(direction& dir) {//获取方向
		dir = t_direction;
	}
	//获取方向

	void get_power(int& power) {//获取威力
		power = t_power;
	}
	//获取威力

	void c_p(point p) {//更改坐标
		t_po = p;
	}
	//更改坐标

	void print_b() {//打印子弹
		gotoxy(t_po);
		cout << "*";
	}
	//打印子弹

	void move() {//直接位移，但考虑到与其他对象进行交互，存疑
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
	//直接位移，但考虑到与其他对象进行交互，对可靠性存疑
};
//子弹类函数

typedef struct tank_node//坦克链表节点
{
	tank data;
	tank_node* next;
	tank_node* prev;
}tank_node;
//坦克链表节点

typedef struct tank_list {//坦克链表，
	tank_node* head;
	int size;
}tank_list;
//坦克链表，其实直接用类也行，只是这样较为直观

typedef struct bb {//子弹链表
	bullet data;
	bb* next;
	bb* prev;
}bb;
//子弹链表节点

typedef struct blist {
	bb* head;
}blist;
//子弹链表，同坦克链表

class tanklist {//坦克链表，增删改查
private:
	tank_list t;
	blist  bt;
public:
	tanklist() {//默认构造函数
		t.head = (tank_node*)malloc(sizeof(tank_node));
		if (!t.head) {//判断头结点是否创建成功
			cout << "头结点" << endl;
			while (1) {
				if (cin.get() != 'y')
				{
					exit(0);
				}
			}
		}

		t.size = 0;
		point p;
		pointdefine(p, 0);//默认玩家点位
		t.head->data = tank(p);//头结点储存玩家信息
		t.head->prev = NULL;//前为空
		t.head->next = NULL;//后为空，用于判断后面是否有节点


		bt.head = (bb*)malloc(sizeof(bb));//子弹头结点
		if (!bt.head) {
			cout << "头结点" << endl;
			while (1) {
				if (cin.get() != 'y')
				{
					exit(0);
				}
			}
		}
		bt.head->next = NULL;
		bt.head->prev = NULL;
		//前为玩家子弹，后为敌人子弹
	}
	//默认构造函数，加入玩家数据

	~tanklist() {//析构函数，删除所有数据
		deleteall();
	}
	//析构函数，删除所有数据，无需额外调用

	void deleteall() {//删除所有数据，释放空间，以免出现空间一直被占用
		tank_node* t1, * t2;
		t1 = t.head->next;
		while (t1 != NULL)//从头结点后面一个开始释放
		{
			t2 = t1->next;//先保留指向下一位置指针，防止空间释放后，找不到下一片内存地址
			free(t1);
			t1 = t2;
		}
		free(t.head);

		bb* b1, * b2;
		b1 = bt.head->next;
		while (b1 != NULL) {//往后释放，且保留头结点
			b2 = b1->next;
			free(b1);
			b1 = b2;
		}
		b1 = bt.head->prev;//往前
		while (b1 != NULL)
		{
			b2 = b1->prev;
			free(b1);
			b1 = b2;
		}
		free(bt.head);//最后释放头结点
	}
	//删除所有数据，释放空间，以免出现空间一直被占用

	//增删改查
	//增

	void tank_add(const point p, int live = 3, int speed = 1, int power = 1, direction direction1 = u) {//增加节点
		tank_node* tnode1 = t.head->next;
		tank_node* tnode2 = NULL;
		tank t0(p, t.size, live, speed, power, direction1);
		point p0;
		tnode2 = (tank_node*)malloc(sizeof(tank_node));
		if (!tnode2)
		{
			cout << "添加节点" << endl;
			cout << "按y退出" << endl;
			while (1) {
				if (cin.get() == 'y')
				{
					exit(0);
				}
			}
		}

		tnode2->data = t0;
		tnode2->data.root_order();

		while (tnode1 != NULL) {//迭代判断，将节点从小到大插入，先判断x，再判断y
			tnode1->data.get_t_po(p0);//获取节点坐标p0
			if (contrast(p0, p)) {//如果返回true，代表p0较小，可继续往后判断，暂时无需插入
				if (tnode1->next == NULL)//如果已经到了最后一位,直接退出循环，用tnode1来储存位置
				{
					break;
				}
				tnode1 = tnode1->next;
				continue;
			}
			else
			{//如果返回false，表示已经到达位置，往前回退一格，并将其插入
				tnode1 = tnode1->prev;
				tnode2->next = tnode1->next;
				tnode2->prev = tnode1;
				tnode1->next = tnode2;
				tnode2->next->prev = tnode2;
				t.size++;
				break;
			}

		}
		if (t.head->next == NULL)//如果头结点后没有数据，直接插入到头结点后
		{
			tnode2->next = t.head->next;
			tnode2->prev = t.head;
			t.head->next = tnode2;
			t.size++;
		}
		if ((tnode1 != NULL) && (tnode1->next == NULL))//如果tnode1非空且tnode1后面为空，表示已经循环到最后一位
		{
			tnode2->next = tnode1->next;
			tnode2->prev = tnode1;
			tnode1->next = tnode2;
			t.size++;
		}

	}
	//增加节点，且节点大小从小到大排列

	void bb_add(const tank_node* tb, bool player = false) {//增加子弹节点
		bb* bnode;
		bullet bbt(tb->data);
		bnode = (bb*)malloc(sizeof(bb));
		if (!bnode)
		{
			cout << "添加子弹节点" << endl;
			while (1) {
				if (cin.get() != 'y')
				{
					exit(0);
				}
			}
		}
		bnode->data = bbt;
		//创建节点，然后放入链表中

		switch (player)//player用来判断是否为玩家子弹，且直接插入到头结点前面
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
	//增加子弹节点,player为false则为敌人子弹

	//删

	void tank_delete(tank_node*& tnode) {//根据指针删除节点

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
	//根据指针删除tank节点

	void bb_delete(bb*& bnode) {//根据指针删除子弹节点
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
	//根据指针删除子弹节点

	//改，移动
	//先写判断函数

	bool distance_calculate_tank_ai(tank_node* tp) {//非玩家tank计算距离，如无问题则返回true
		point a, b;
		tp->data.get_t_po(a);
		tank_node* t0;
		t0 = tp->prev;
		while (!(t0 == t.head)) {//往前一直到头结点后面一个
			t0->data.get_t_po(b);
			t0 = t0->prev;
			if ((a.x - b.x) * (a.x - b.x) < 9) {//计算x，如果差小于3，则判断y，如果大于三则结束
				if ((a.y - b.y) * (a.y - b.y) < 9) {//如果y的差也小于3，返回false，
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
		while (t0 != NULL)//往后一直到最后
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
		if ((a.x - b.x) * (a.x - b.x) < 9)//最后判断与玩家的距离
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
	//非玩家tank之间相互计算距离，如无问题则返回true

	bool distance_calculate_player() {//玩家坦克距离计算，如无问题则返回true
		tank_node* tnode = t.head->next;
		point player, p;
		t.head->data.get_t_po(player);
		while (tnode != NULL) {//循环往后，且x从小到大
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
			else if ((p.x - player.x) > 3)//如果该节点的x比player.x大3，则后面一定大3，直接返回true
			{
				return true;
			}
			else
			{
				continue;
			}
		}
		return true;//如循环结束依旧没有返回false，则表示无问题
	}
	//玩家坦克与其他坦克的距离计算，如无问题则返回true

	bool tank_move_judge(tank_node* tnode, bool flag) {//判断函数，用于判断坦克位移是否能成功
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
	//判断函数，用于判断坦克位移是否能成功，flag用于确定是玩家还是ai

	void tank_move(tank_node* tnode, direction dir = u, bool flag = false) {//坦克移动函数
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
	//坦克移动函数

	void tank_do(tank_node* tnode) {//单个坦克行动
		direction dir;
		srand(ran);
		ran = rand();
		dir = (direction)(ran % 4);
		unsigned int random;
		random = ran;
		srand(ran);//更换种子，以免出现概率不够
		ran = rand();
		if ((ran % 4) == 1)
		{
			tnode->data.c_direction(dir);
		}
		srand(ran);
		ran = rand();
		if ((ran % 2) == 1)//二分之一概率移动
		{
			tank_move(tnode);
		}
		srand(ran);
		ran = rand();
		if ((ran % 7) == 1)//七分之一概率攻击
		{
			bb_add(tnode, false);
		}
	}
	//单个坦克行动，转向、移动、攻击

	void tank_do_all() {//全部坦克行动
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
	//全部坦克行动,后面直接调用，忽略掉其他

	void bb_move(bb* bnode) {//子弹移动函数
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
	//子弹移动函数

	void bb_move_all() {//全部子弹移动函数
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
	//全部子弹移动函数

	void player_tank_move(direction dir) {//玩家坦克移动
		t.head->data.c_direction(dir);
		tank_move(t.head, dir, true);
	}
	//玩家坦克移动

	void player_attack() {//玩家坦克攻击
		bb_add(t.head, true);
	}
	//玩家坦克攻击

	void move_all() {//所有单位进行运动
		bb_move_all();
		tank_do_all();
	}
	//所有单位进行运动

	//查

	void get_size(int& s) {	//获得类的大小
		s = t.size;
	}
	//获得类的大小

	void get_tank( point& p, int& live, int& power, int& speed, direction& direction1, tank_node* tnode = NULL) {//获取坦克信息
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
	//获取坦克信息

	//排序

	bool order() {//检查排序结果
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
	//检查排序结果

	void root_order() {//排序标记归零
		tank_node* tnode = t.head->next;
		while (tnode != NULL)
		{
			tnode->data.root_order();
			tnode = tnode->next;
		}
	}
	//排序标记归零

	void order_tank() {//排序
		tank_node* t2 = t.head->next;
		tank_node* t1;
		tank_node* tnode;
		point a, b, c;
		while (t2->next != NULL)//循环到尾部前一个
		{
			t1 = t2->next;//顺序为head、……、t2、t1、……
			t2->data.get_t_po(a);
			t1->data.get_t_po(b);
			if (contrast(a, b))//假如a小于b，继续后移，且更改t2的标记
			{
				t2->data.c_order();
				t2 = t1;
			}
			else//假如a大于b，表示b较小，t1需要前移
			{
				tnode = t2->prev;
				tnode->data.get_t_po(c);
				while ((!contrast(c, b)) && (tnode != t.head))//一直前移到c小于b或者，tnode为头结点，停下
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
	//坦克排序

	//交互

	int distance_calculate_bb_and_tank(tank_node* tnode = NULL, bool flag = true) {//检查子弹与单个坦克的交互，然后进行删除
		bb* bnode = bt.head;
		bb* kill;
		point b, p;
		int power;
		if (flag)
		{
			t.head->data.get_t_po(p);
			bnode = bt.head->prev;
			while (bnode != NULL)//先将玩家与己方子弹进行判断，消除掉接触的子弹
			{
				kill = bnode;
				bnode = bnode->prev;
				kill->data.get_p(b);
				if (b == p)
				{
					bb_delete(kill);
				}
			}
			//玩家与ai子弹
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
			while (bnode != NULL)//先将ai与ai子弹进行判断，消除掉接触的子弹
			{
				kill = bnode;
				bnode = bnode->next;
				kill->data.get_p(b);
				if (b == p)
				{
					bb_delete(kill);
				}
			}
			//ai与玩家子弹交互
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
	//检查坦克节点与子弹的交互，然后进行删除 ，默认为玩家与敌方子弹,返回值为子弹威力

	void hit_tank() {//将接触到坦克的子弹消除掉，并反馈给该坦克伤害
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
	//将接触到坦克的子弹消除掉，并反馈给该坦克伤害

	void tank_kill() {//将生命值不足1的坦克删除，如玩家生命不足将结束游戏
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
	//将生命值不足1的坦克删除

	void bb_kill() {//将墙外子弹删除
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
	//将墙外子弹删除

	void kill() {//进行上述三个操作，先删除墙外子弹，然后坦克子弹互动，后删除坦克
		bb_kill();
		hit_tank();
		tank_kill();
	}
	//进行上述三个操作，先删除墙外子弹，然后坦克子弹互动，后删除坦克,直接调用该函数

	void print_all() {//打印所有单位
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
	//打印所有单位
};
