#include<iostream>
#include<cstring>

using namespace std;
int read(){//���ٶ��� ���Լ��� 
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
	UP, DOWN, LEFT, RIGHT
};
struct Robot{
	Position pos;
	Direction dir;//���� 
};
struct Light{
	Position pos;//�Ƶ�λ�� 
	bool lighten;//1��ʾ������ 
};
// ��Ԫ������
struct Cell {
 	int height; // �߶�
 	int light_id; // �Ʊ�ʶ��-1��ʾ�õ�Ԫ����û�е� 1��ʾ�е� 
 	bool robot; // true/false�ֱ��ʾ��������/���ڸõ�Ԫ����
};
// ָ������
enum OpType {
 	TL, TR, MOV, JMP, LIT, CALL
};
// TLΪ��ת��TRΪ��ת��MOVΪ��ǰ���ߣ�JMPΪ��Ծ��LITΪ�����ƣ�
// ʹ��CALL��ʾ����MAIN��CALL + 1��ʾ����P1���Դ����ơ�
// ��������
struct Proc {
 	OpType ops[MAX_OPS]; // ָ���¼��MAX_OPSΪ������
 	int count; // ��Чָ����
};
// ָ����������
struct OpSeq {
 // ���̼�¼��MAX_PROCSΪ������
 // procs[0]ΪMAIN���̣�procs[1]ΪP1���̣��Դ�����
 	Proc procs[MAX_PROCS];
 	int count; // ��Ч������
};
// ��ͼ״̬����
struct Map {
 // ��Ԫ����ɶ�ά���飬MAX_ROW��MAX_COLΪ������
	Cell cells[MAX_ROW][MAX_COL];
	int row, col; // ��Ч��������Ч����
 // �Ƽ�¼��MAX_LITΪ������
 	Light lights[MAX_LIT];
 	int num_lights; // ��Ч����
 // ��ͼ��ͬʱֻ��һ��������
 	Robot robot;
 // ÿ�����̵�ָ��������
 	int op_limit[MAX_PROCS];
};
// ��Ϸ״̬����
struct Game {
 	char map_name[MAX_PATH_LEN]; // ��ǰ��ͼ���ļ�·����
 	Map map_init; // ��ͼ��ʼ״̬
 	Map map_run; // ָ��ִ�й����еĵ�ͼ״̬
 // �Զ�������ļ�·������MAX_PATH_LENΪ������
 	char save_path[MAX_PATH_LEN];
    int auto_save_id; // �Զ������ʶ   �涨�� 0:����Ҫ�Զ�����   1: ��Ҫ�Զ����� 
 	
	 
	int limit; // �������ޣ������������޵ݹ飩
	int proc_num_limit;//������������ 
	int proc_limit[MAX_PROS];//ÿ������ ָ������ 
 	
 	OpSeq opseq;//��������
};
Game game; // ȫ��Ψһ��Game����


enum ResultType{
	ERROR_READ,//�½� �������в��Ϸ����������ƣ� 
	LIGHT,//�Ѿ��������е� 
	LIMIT,//�ﵽ���������� 
	DARK//MAIN��� 
};



struct Result{
	int steps;//�ܲ��� 
	ResultType result;
};

//����Ϊģ���ڲ������뺯�� 
struct map_drawing{//��ͼģ�� 
	
}module_1;

struct operation{//ִ��ģ�� 
	void compiling_op(){//���������д���Obseq
	//Obseq ���ж�� Proc
	//struct Proc {
	// 	OpType ops[MAX_OPS]; // ָ���¼��MAX_OPSΪ������
	// 	int count; // ��Чָ����
	//}; 
	
	}
	Result error_return(){
		Result ans;
		ans.steps = 0;
		ans.result = ERROR_READ;
		return ans;
	}
	OpType op_reader(){//���ַ���ת��ΪOptype  undone
		char use[10];
		OpType ans;
		if(strcmp(use,"LIT") == 0)ans = LIT;
		else if(strcmp(use,"JMP") == 0)ans = JMP;
		else if(strcmp(use,"MOV") == 0)ans = MOV;
		else if(strcmp(use,"TL") == 0)ans = TL;
		else if(strcmp(use,"TR") == 0)ans = TR;
		else if(use[0] == 'P'){
			int x = 0;
			for(int i = 1; i < strlen(use); i++){//����P��������� 
				x *= 10;
				x += use[i] - '0';
			}
			ans = CALL;//unsolve
		}
	}
	bool check_light(){//�����Ƿ�ȫ������ 
		for(int i = 1; i <= game.map_init.num_lights; i++){
			if(game.map_init.lights[i].lighten == 0)return 0;
		}
		return 1;
	}

	Result Robot_run(const char *path){//ִ����������  �����ļ�·������ 
		freopen("path", "r", stdin);
		//undone prework ���һģ��Ľ���δ��� 
		Result ans;
		ans.steps = 0;
		//������������  �޸�opseq 
		game.opseq.count = read();//���̸��� 
		if(game.opseq.count > game.proc_num_limit)return error_return();
		for(int i = 0; i < game.opseq.count; i++){
			game.opseq.procs[i].count = read();//ÿ��������������е�ָ�����
			if(game.opseq.procs[i].count > game.proc_limit[i])return error_return();
			for(int j = 0; j < game.opseq.procs[i].count; j++){
				game.opseq.procs[i].ops[j] = op_reader();//unsolve 
			}
		}
	
		//ִ����������  ��ִ����������procs[0] 
		for(int i = 0; i < game.opseq.procs[0].count; i++){
		
		}
	
		freopen("CON", "r", stdin);
	}
}module_2;






struct order{//����ģ�麯�� 
	char use[MAX_PATH_LEN];//���ڶ�ȡ��ַ�� �ַ�������
	Direction dir_reader(int x){
		Direction ans;
		if(x == 0)ans = UP;
		else if(x == 1)ans = DOWN;
		else if(x == 2)ans = LEFT;
		else ans = RIGHT;
		return ans;
	}
	void LOAD(){//���ص�ͼ  done
		cin >> game.map_name;//��map_nameΪ��ַ���ص�ͼ 
		freopen(game.map_name,"r",stdin);
		int row = 
		game.map_init.row = read();
	
		int col =
		game.map_init.col = read();
	
		game.map_init.num_lights = read();
	
		game.proc_num_limit = read();//��������� ���ֵ
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				game.map_init.cells[i][j].height = read();
			}
		} 
	
		for(int i = 1; i <= game.map_init.num_lights; i++){
			int xx = game.map_init.lights[i].pos.y = read();
			int yy = game.map_init.lights[i].pos.x = read();//����λ��
			
			game.map_init.lights[i].lighten = 0;//��ʼ�� ״̬Ϊ�� 
						
			game.map_init.cells[xx][yy].light_id = 1;//�е� 
		}
	
		for(int i = 0; i < game.proc_num_limit; i++){//����ÿ�����̵Ĳ������� 
			game.proc_limit[i] = read();//һ��pocs ��һ������ һ��������һ��ָ� 
		}
		game.map_init.robot.pos.y = read();
		game.map_init.robot.pos.x = read();
		game.map_init.robot.dir = dir_reader(read());
		freopen("CON","r",stdin);
	}
	void AUTOSAVE(){//�����Զ�����  done
		cin >> use;
		if(use[0] == 'O'){
			game.auto_save_id = 0;//�ر��Զ����� 
		}
		else{
			strcpy(game.map_name, use);//�����Զ����� ��use����ȫ�ֱ��� ����ģ��� ��һ��ʵ���Զ����� 
		}
	}
	void Modify_Limit(){//�޸Ĳ������� done
		int x;
		cin >> x;
		game.limit = x;//�޸Ĳ������ޣ�ȫ�ֱ����� 
	}
	void Print_cell(bool is_robot, int light, int height){
	//�Ƿ��л�����  �� ��0  ��1 ��2 �߶�
		if(height == 0)return;
		if(is_robot){//�л����� 
			//cout << "/e[RED_FRONT;GREY_BACK;BLODm" << height;
			if(light == 0)cout << "\e[91;100;1m" << height;
			else if(light == 1)cout << "\e[91;104;1m" << height;
			else cout << "\e[91;103;1m" << height;
		}
		else if(light == 0){//��ͨ���� 
			cout << "\e[92;100;1m" << height;
		}
		else if(light == 1){//����ĵ� 
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
						light++;//01 ��� 12
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
	void Print_Status(){//�����ǰ״̬ 
		cout << "Map Name: " << game.map_name << endl;
		cout << "Autosave: ";
		if(game.auto_save_id = 1)cout << game.save_path << endl;
		else cout << "OFF" << endl;
		cout << "Step Limit: " << game.limit << endl;
		Print_map(game.map_init);//�������� ��ӡ���԰��ͼ
		
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
	void Modify_op(){//�༭ָ������ ���½���  done
		cin >> use;
		freopen("use", "w", stdout);
		int n = read();
		cout << n << endl;
		for(int i = 1; i <= n; i++){
			string nd;//���������⣨need��
			getline(cin, nd);
			cout << nd << endl; 
		}
		freopen("CON", "w", stdout);
	}
	void info(int sign){//������Ϣ 
		if(sign == 1)cout << "��ǰ�ļ�������" << endl;
	}
	void Run(){//ִ��ָ������ 
		cin >> use;
		//�����ڶ�ģ�� ִ�� Robot_run
		// ���� ����ԭ��   +   ����  
		Result rs = module_2.Robot_run(use);
		cout << "Step(s) used: " << rs.steps <<endl; //���� 
		//������ӡ��Ϣ 
		
	}
}od;





void work(){
	char s[10];//LOAD AUTOSAVE LIMIT STATUS OP RUN EXIT 
	while(1){
		cin >> s;
		if(s[0] == 'E'){
			return;
		}
		if(s[0] == 'L' && s[1] == 'O'){//���ص�ͼ 
			od.LOAD();
		}
		else if(s[0] == 'A'){//�����Զ����� 
			od.AUTOSAVE();
		}
		else if(s[0] == 'L'){//���ò������� 
			od.Modify_Limit();
		}
		else if(s[0] == 'S'){//������� 
			od.Print_Status();
		}
		else if(s[0] == 'O'){//�༭ָ������ 
			od.Modify_op();
		}
		else if(s[0] == 'R'){//RUN
			od.Run();
		}
	}
}
int main(){
	work();
	//od.LOAD();
	//od.Print_Status();
}
