#include<bits/stdc++.h>
using namespace std;
enum ResultType {
	LIGHT, // 结束条件1，点亮了全部灯，干得漂亮
	LIMIT, // 结束条件2，到达操作数上限
	DARK // 结束条件3，MAIN过程执行完毕
};
// 执行结果类型
struct Result {
 int steps; // 记录总步数
 ResultType result; // 用enum记录结束原因
};
int main(){
}
