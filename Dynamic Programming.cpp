#include<iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Object{
    public:
        int value;
        int weight;

        Object(int value, int weight):value(value), weight(weight){};
};

vector<Object> generate_objects(int n){
    vector<Object> object_list = {};

    cout<<"Manual (m) or random (r) input: ";
    char input;
    cin>>input;
    if(input == 'r'){
        srand(time(nullptr));

        for(int i = 0; i < n; i++){
            object_list.push_back(Object(rand() % 9 + 1,rand() % 9 + 1));
        }
    }
    else{
        int value = 0;
        int weight = 0;
        for(int i = 0; i < n;i++){
            cout<<"Input value for object no."<<i+1<<": ";
            cin>>value;
            cout<<"Input weight for object no."<<i+1<<": ";
            cin>>weight;
            object_list.push_back(Object(value, weight));
        }
    }
    
    return object_list;
}

void print_objects(vector<Object> object_list){
    int len = object_list.size();
    for(int i = 0; i< len;i++){
        cout<<object_list[i].value<<"    "<<object_list[i].weight<<"     \n";
    }
}

void Knapsack(int n, int w){
    vector<Object> object_list = generate_objects(n);

    int result_table[n+1][w+1];
    int result[n];

    //--------------------------------------------Calculating result table----------------------------------------------------------
    //First row (empty row) is filled with 0
    for(int i = 0; i<=w;i++){
        result_table[0][i] = 0;
    }

    //Start filling other rows
    for(int i = 1; i <= n;i++){
        for(int j = 0; j <= w;j++){
            if(j - object_list[i-1].weight < 0){
                result_table[i][j] = result_table[i-1][j];
            }
            else{
                int temp = object_list[i-1].value + result_table[i-1][j - object_list[i-1].weight];
                if(temp > result_table[i-1][j]){
                    result_table[i][j] = temp;
                }
                else{
                    result_table[i][j] = result_table[i-1][j];
                }
            }
        }
    }

    //Finding which items is included in the knapsack
    //Traversing backward from last to first object
    int current_weight = w;
    for(int i = n; i >= 1; i--){
        int current_value = result_table[i][current_weight];
        if(current_value != result_table[i-1][current_weight]){
            result[i-1] = 1;
            current_weight = current_weight - object_list[i-1].weight;
        }
        else{
            result[i-1] = 0;
        }
    }
    //--------------------------------------------Displaying result table-------------------------------------------------------------
    cout<<"\n\n\nObject No.    Value    Weight  ";
    for(int i = 0; i <= w;i++ ){
        cout<<"_"<<i<<"_";
    }
    cout<<"\n";
    for(int i = 0; i <= n;i++){
        if(i == 0){
            cout<<"                   Empty     ";
        }
        else{
            cout<<"    "<<i<<"           "<<object_list[i-1].value<<"         "<<object_list[i-1].weight<<"  ";
        }
        cout<<"  |";
        for(int j = 0; j <= w;j++){
            cout<<result_table[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"The optimal value is "<<result_table[n][w]<<endl;
    cout<<"Objects that are included are: ";
    for(int i = 0; i<n;i++){
        if(result[i] == 1){
            cout<<i+1<<"  ";
        }
    }
}

int main(){
    cout<<"Input amount of n objects"<<endl;
    int n;
    cin>>n;
    cout<<"Input weight w of the knapsack"<<endl;
    int w;
    cin>>w;

    Knapsack(n, w);

    return 0;
}