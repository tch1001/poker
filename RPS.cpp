#include <bits/stdc++.h>

using namespace std;

// 0 = rock, 1 = paper, 2 = scissors
double payoff[3][3][2] = {
    {{0,0},{-1,1},{1,-1}},
    {{1,-1},{0,0},{-1,1}},
    {{-1,1},{1,-1},{0,0}}
};

double regret[3] = {0,0,0};
double strategy[3] = {0,0,0};

int action(){
    double sum = 0;
	for(int i=0;i<3;i++){
		sum += max(0.0,regret[i]);
	}
    double r = (double)rand()/RAND_MAX;
	double cum_prob = 0;
	for(int i=0;i<3;i++){
		if(sum > 0) cum_prob += max(0.0,regret[i])/sum;
        else cum_prob += 1.0/3;
		if(r <= cum_prob){
			return i;
		}
	}
    assert(false);
}

double B_strat[3] = {0.3,0.3,0.3};
int B_strategy(){
    while(true){
        double r = (double)rand()/RAND_MAX;
        double cum_prob = 0;
        for(int i=0;i<3;i++){
            cum_prob += B_strat[i];
            if(r < cum_prob){
                return i;
            }
        }
    }
}

void play(){
    int A = action();
    int B = B_strategy(); // always play rock
    for(int i=0;i<3;i++){ // regret for not playing each action
        // the more i regret not playing an action, the more likely i am to play it
        regret[i] += payoff[i][B][0] - payoff[A][B][0];
    }
}
void train(){
    for(int i=0;i<10000000;i++){
        play();
    }
}

int main(){
    // seed random
    srand(43);
    train();
    for(int i=0;i<3;i++){
        cout << regret[i] << " ";
    }
    cout << endl;
    return 0;
}
