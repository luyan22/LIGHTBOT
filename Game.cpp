#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
using namespace std;
int read(){//快速读入 忽略即可 
	char s;
	int x = 0, f = 1;
	s = getchar();
	while(s < '0' || s > '9'){
		if(s == '-')f = -1;
		s = getchar();
	}
	while(s >= '0' && s <= '9'){
		x *= 10;
		x += s - '0';
		s = getchar();
	}
	
	return x * f;
}

const int MAX_OPS = 50, MAX_PROCS = 50;
const int MAX_ROW = 50,MAX_COL =  50;
const int MAX_LIT = 50, MAX_PROS = 50;
const int MAX_PATH_LEN = 50;


struct Position{
	int x, y;
};
enum Direction{
	UP, RIGHT, DOWN, LEFT//逆时针 
};
struct Robot{
	Position pos;
	Direction dir;//朝向 
	int step_run = 0;//已经走了的步数 
};
struct Light{
	Position pos;//灯的位置 
	bool lighten;//1表示被点亮 
};
// 单元格类型
struct Cell {
 	int height; // 高度
 	bool robot; // true/false分别表示机器人在/不在该单元格上
};
// 指令类型
enum OpType {
 	TL, TR, MOV, JMP, LIT, CALL
};
// TL为左转，TR为右转，MOV为向前行走，JMP为跳跃，LIT为点亮灯；
// 使用CALL表示调用MAIN，CALL + 1表示调用P1，以此类推。
// 过程类型
struct Proc {
 	OpType ops[MAX_OPS]; // 指令记录，MAX_OPS为合理常数
 	int count; // 有效指令数
};
// 指令序列类型
struct OpSeq {
 // 过程记录，MAX_PROCS为合理常数
 // procs[0]为MAIN过程，procs[1]为P1过程，以此类推
 	Proc procs[MAX_PROCS];
 	int count; // 有效过程数
};
// 地图状态类型
struct Map {
 // 单元格组成二维数组，MAX_ROW、MAX_COL为合理常数
	Cell cells[MAX_ROW][MAX_COL];
	int row, col; // 有效行数、有效列数
 // 灯记录，MAX_LIT为合理常数
 	Light lights[MAX_LIT];
 	int num_lights; // 有效灯数
 // 地图上同时只有一个机器人
 	Robot robot;
 // 每个过程的指令数限制
 	int op_limit[MAX_PROCS];
};
// 游戏状态类型
struct Game {
 	char map_name[MAX_PATH_LEN]; // 当前地图的文件路径名
 	Map map_init; // 地图初始状态
 	Map map_run; // 指令执行过程中的地图状态
 // 自动保存的文件路径名，MAX_PATH_LEN为合理常数
 	char save_path[MAX_PATH_LEN];
    int auto_save_id; // 自动保存标识   规定： 0:不需要自动保存   1: 需要自动保存 
 	
	 
	int limit; // 步数上限（用来避免无限递归）
	int proc_num_limit;//过程数量上限 
	int proc_limit[MAX_PROS];//每个过程 指令上限 
 	
 	OpSeq opseq;//过程序列
};
Game game; // 全局唯一的Game变量


enum ResultType{
	LIGHT,//已经点亮所有灯 
	LIMIT,//达到操作数上限 
	DARK//MAIN完成 
};



struct Result{
	int steps;//总步数 
	ResultType result;
};

//以下为模块内部变量与函数 
struct map_drawing{//绘图模块 
	
}module_1;

struct operation{//执行模块 
	int xx[4] = {-1, 0, 1, 0};//前进时用于确定具体坐标变化 
	int yy[4] = {0, 1, 0, -1};//上右下左 
	void compiling_op(){//将命令序列存入Obseq
	//Obseq 中有多个 Proc
	//struct Proc {
	// 	OpType ops[MAX_OPS]; // 指令记录，MAX_OPS为合理常数
	// 	int count; // 有效指令数
	//}; 
	
	}
//	Result error_return(){
//		Result ans;
//		ans.steps = 0;
//		ans.result = ERROR_READ;
//		return ans;
//	}
	OpType op_reader(){//将字符串转化为Optype  done
		char use[10];
		OpType ans;
		cin >> use; 
		//cout << use << endl;
		if(use[0] == 'L')ans = LIT;
		else if(use[0] == 'J')ans = JMP;
		else if(use[0] == 'M')ans = MOV;
		else if(use[0] == 'T' && use[1] == 'L')ans = TL;
		else if(use[0] == 'T')ans = TR;
		else if(use[0] == 'P'){
			int x = 0;
			for(int i = 1; i < strlen(use); i++){//读入P后面的数字 
				x *= 10;
				x += use[i] - '0';
			}
			ans = (OpType)(CALL + x);
			
		}
		return ans;
	}
	bool check_light(){//检查灯是否全被点亮 
		for(int i = 0; i < game.map_init.num_lights; i++){
			if(game.map_init.lights[i].lighten == 0)return 0;
		}
		return 1;
	}
	
	void Proc_run(int id){//以一个过程为单位  输入过程编号 
		//cout << check_light() << endl;
		if(check_light())return;
		for(int j = 0; j < game.opseq.procs[id].count; j++){
			//cout << game.map_run.robot.pos.x <<" "<<
//			game.map_run.robot.pos.y << " " << 
//			game.map_run.cells[game.map_run.robot.pos.x][game.map_run.robot.pos.y]
//			.height<< endl;
			//cout << j << " " << game.opseq.procs[id].ops[j] << endl;
			if(game.map_run.robot.step_run > game.limit)break;//超过步数限制了 
			if(check_light())break; 
			game.map_run.robot.step_run += 1;
			if(game.opseq.procs[id].ops[j] == TL){//顺时针旋转 右转加一 
				game.map_run.robot.dir 
				= (Direction)((game.map_run.robot.dir + 3) % 4);
			} 
			else if(game.opseq.procs[id].ops[j] == TR){
				game.map_run.robot.dir 
				= (Direction)(game.map_run.robot.dir + 1 % 4);
			}
			else if(game.opseq.procs[id].ops[j] == MOV){
				int x = game.map_run.robot.pos.x;
				int y = game.map_run.robot.pos.y;
				int d = game.map_run.robot.dir;
				int new_x = game.map_run.robot.pos.x + xx[d];
				int new_y = game.map_run.robot.pos.y + yy[d];
//				cout << d << endl;
//				cout << x << " "<< y << " "<< new_x << " " << new_y << endl;
				if(new_x < 0 || new_x > game.map_init.row //有待讨论 
				|| new_y < 0 || new_y > game.map_init.col)continue;
				if(game.map_init.cells[new_x][new_y].height == 0)continue;
				
//				cout << new_x << " " << new_y << endl;
//				cout << game.map_init.cells[x][y].height << 
//				game.map_init.cells[new_x][new_y].height << endl;
				if(game.map_init.cells[x][y].height != 
				game.map_init.cells[new_x][new_y].height)continue;//高度不同 忽略 
				game.map_run.robot.pos.x = new_x;
				game.map_run.robot.pos.y = new_y;
				
			}
			else if(game.opseq.procs[id].ops[j] == JMP){
				int x = game.map_run.robot.pos.x;
				int y = game.map_run.robot.pos.y;
				int d = game.map_run.robot.dir;
				int new_x = game.map_run.robot.pos.x + xx[d];
				int new_y = game.map_run.robot.pos.y + yy[d];
				
				if(abs(game.map_init.cells[x][y].height - 
				game.map_init.cells[new_x][new_y].height)
				!= 1)continue;//高度不相差1 忽略 
				game.map_run.robot.pos.x = new_x;
				game.map_run.robot.pos.y = new_y;
			}
			else if(game.opseq.procs[id].ops[j] == LIT){
				int x = game.map_run.robot.pos.x;
				int y = game.map_run.robot.pos.y;
				//cout << "LIT" << x << " " << y << endl;
				for(int i = 0; i < game.map_init.num_lights; i++){
					if(game.map_init.lights[i].pos.x == x && 
					game.map_init.lights[i].pos.y == y){
						game.map_run.lights[i].lighten = 1;
					}
				}
			}
			else if(game.opseq.procs[id].ops[j] >= CALL){//处理 CALL 
				int k = game.opseq.procs[id].ops[j] - CALL;
				Proc_run(k);
			}
		}
		return;
	}
	
	Result Robot_run(const char *path){//执行命令序列  读入文件路径名称 
		freopen(path, "r", stdin);
		//undone prework 与第一模块的交互未完成 
		Result ans;
		//读入命令序列  修改opseq 
		game.opseq.count = read();//过程个数 
		for(int i = 0; i < game.opseq.count; i++){
			game.opseq.procs[i].count = read();//每个读入的命令序列的指令个数
			for(int j = 0; j < game.opseq.procs[i].count; j++){
				//cout << op_reader() << endl;
				game.opseq.procs[i].ops[j] = op_reader();
			}
		}
		
		cout<<"开始执行"<<endl;
		//执行命令序列  仅执行命令序列procs[0] 
		game.map_run = game.map_init;
		//**未完成init与run的转化 
		Proc_run(0);
		game.map_init = game.map_run;
		
//		for(int i = 0; i < game.map_init.num_lights; i++){
//			cout << game.map_init.lights[i].lighten << endl;
//		}
		//cout<<"zyzy"<<check_light();
		if(check_light())ans.result = LIGHT;
		else if(game.map_run.robot.step_run > game.limit)ans.result = LIMIT;
		else ans.result = DARK;
	
		freopen("CON", "r", stdin);
		return ans;
	}
}module_2;






struct order{//交互模块函数 
	char use[MAX_PATH_LEN];//用于读取地址等 字符串变量
	Direction dir_reader(int x){
		Direction ans;
		if(x == 0)ans = UP;
		else if(x == 1)ans = DOWN;
		else if(x == 2)ans = LEFT;
		else ans = RIGHT;
		return ans;
	}
	void LOAD(){//加载地图  done
		cin >> game.map_name;//以map_name为地址加载地图 
		freopen(game.map_name,"r",stdin);
		int row = 
		game.map_init.row = read();
	
		int col =
		game.map_init.col = read();
	
		game.map_init.num_lights = read();
	
		game.proc_num_limit = read();//读入过程数 最大值
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				game.map_init.cells[i][j].height = read();
			}
		} 
	
		for(int i = 0; i < game.map_init.num_lights; i++){
			int xx = game.map_init.lights[i].pos.y = read();
			int yy = game.map_init.lights[i].pos.x = read();//读入位置
			
			game.map_init.lights[i].lighten = 0;//初始化 状态为灭 		
		}
	
		for(int i = 0; i < game.proc_num_limit; i++){//读入每个过程的操作上限 
			game.proc_limit[i] = read();//一个pocs 是一个过程 一个过程是一个指令串 
		}
		game.map_init.robot.pos.y = read();
		game.map_init.robot.pos.x = read();
		game.map_init.robot.dir = dir_reader(read());
		freopen("CON","r",stdin);
	}
	void AUTOSAVE(){//设置自动保存  done
		cin >> use;
		//cout << use << endl;
		if(use == "OFF"){
			game.auto_save_id = 0;//关闭自动保存 
		}
		else{
			game.auto_save_id = 1;
			strcpy(game.save_path, use);//开启自动保存 将use传给全局变量 用于模块二 进一步实现自动保存 
		}
		cout << game.auto_save_id << endl;
	}
	void Modify_Limit(){//修改步数上限 done
		int x;
		cin >> x;
		game.limit = x;//修改步数上限（全局变量） 
	}
	void Print_cell(bool is_robot, int light, int height){
	//是否有机器人  灯 无0  灭1 亮2 高度
		if(height == 0)return;
		if(is_robot){//有机器人 
			//cout << "/e[RED_FRONT;GREY_BACK;BLODm" << height;
			if(light == 0)cout << "\e[91;100;1m" << height;
			else if(light == 1)cout << "\e[91;104;1m" << height;
			else cout << "\e[91;103;1m" << height;
		}
		else if(light == 0){//普通格子 
			cout << "\e[92;100;1m" << height;
		}
		else if(light == 1){//有灭的灯 
			cout << "\e[92;104;1m" << height;
		}
		else{
			cout << "\e[92;103;1m" << height;
		}
		cout << "\e[0m";
		return;
	}
	void Print_map(Map readin){
		for(int i = 0; i < readin.row; i++){
			for(int j = 0; j < readin.col; j++){
				bool is_robot = (readin.robot.pos.x == i && readin.robot.pos.y == j) ?
				1 : 0; 
				//cout<<is_robot<<endl;
				int light = 0;
				for(int k = 1; k <= readin.num_lights; k++){
					if(readin.lights[k].pos.x == i && readin.lights[k].pos.y == j){
						light = readin.lights[k].lighten;
						light++;//01 变成 12
						break; 
					}
				}
				Print_cell(is_robot,light,readin.cells[i][j].height);
			}cout << endl;
		}
	}
	void print_robot_dir(Direction a){
		if(a == UP)cout << "up";
		else if(a == DOWN)cout << "down";
		else if(a == LEFT)cout << "left";
		else cout << "right";
	}
	void Print_Status(){//输出当前状态 
		cout << "Map Name: " << game.map_name << endl;
		cout << "Autosave: ";
		if(game.auto_save_id == 1)cout << game.save_path << endl;
		else cout << "OFF" << endl;
		cout << "Step Limit: " << game.limit << endl;
		Print_map(game.map_init);//在命令行 打印简略版地图
		
		cout << "Robot is facing ";
		print_robot_dir(game.map_init.robot.dir);
		cout << "." << endl;
		
		cout << "Proc Limit: [" ;
		for(int i = 0; i < game.proc_num_limit; i++){
			if(i != 0)cout << ", ";
			cout << game.proc_limit[i];
		}
		cout << "]" << endl;
	}
	void info(int sign){//给出信息 
		if(sign == 1)cout << "当前文件不存在" << endl;
		else if(sign == 2)cout << "输入指令序列超出地图上限" << endl; 
	}
	void Modify_op(){//编辑指令序列 （新建）  done 已经加入判断指令数超过地图上限 
		cin >> use;
		cout << use << endl;
		freopen(use,"w",stdout);
		//cout << use << endl;
		int n = read();
		cout << n << endl;
		for(int i = 1; i <= n; i++){
			string nd;//命名很随意（need）
			getline(cin, nd);
			cout << nd << endl; 
		}
		freopen("CON", "w", stdout);
		
//		cout << game.proc_num_limit << endl;
//		for(int i = 0; i < game.proc_num_limit; i++){
//			cout<<game.proc_limit[i]<<endl;
//		}
		
		freopen(use,"r",stdin);//开始判断读入序列是否合法 
		int check = 1;
		int op_num = read();
		if(op_num > game.proc_num_limit)check = 0;
		for(int i = 0; i < op_num; i++){
			int x = read();
			if(x > game.proc_limit[i])check = 0;
			for(int j = 1; j <= x; j++){
				cin >> use;
			}
		}
		if(!check)info(2);
		else cout << "成功读入序列" << endl; 
		freopen("CON","r",stdin);
	}
	void Run(){//执行指令序列 
		cin >> use;
		//交给第二模块 执行 Robot_run
		// 返回 结束原因   +   步数  
		Result rs = module_2.Robot_run(use);
		cout << "Step(s) used: " << game.map_run.robot.step_run <<endl; //当前花费的步数 
		//继续打印信息 
		if(rs.result == LIGHT){
			cout << "恭喜你！顺利通过游戏" << endl;
		}
		if(rs.result == DARK){
			cout << "已完成所有步骤" << endl;
		}
		else if(rs.result == LIMIT){
			cout << "已经到达步数上限" << endl; 
		}
	}
}od;





void work(){
	char s[10];//LOAD AUTOSAVE LIMIT STATUS OP RUN EXIT 
	while(1){
		cin >> s;
		//cout << s[0] << endl;
		if(s[0] == 'E'){
			return;
		}
		if(s[0] == 'L' && s[1] == 'O'){//加载地图 
			od.LOAD();
		}
		else if(s[0] == 'A'){//设置自动保存 
			od.AUTOSAVE();
		}
		else if(s[0] == 'L'){//设置步数限制 
			od.Modify_Limit();
		}
		else if(s[0] == 'S'){//输出配置 
			od.Print_Status();
		}
		else if(s[0] == 'O'){//编辑指令序列 
			od.Modify_op();
		}
		else if(s[0] == 'R'){//RUN
			od.Run();
		}
	}
}
int main(){
//	Direction a = LEFT;
//	cout << a << endl;
	work();
	//od.LOAD();
	//od.Print_Status();
}
