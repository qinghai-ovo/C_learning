#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define HASHSIZE 101
#define FNVPrime 16777619U
#define FNVOffsetBasis 2166136261U

//Use cities`s name as hashtable`s index aka key.
struct city *cityHashtable[HASHSIZE];
static int cityTableLoad[HASHSIZE];

//This is a hash table for "search by country" function, use country name as hashtable`s index aka key.
struct city *countryHashtable[HASHSIZE];

//In each struct include the city name, lat, lng, countryname, citypop, pointer to next city in the same hash block
typedef struct city{
    char *cityName; /* 都市名 */
    float lat; /* 緯度 */
    float lng; /* 経度 */
    char *countryName; /* 国名 */
    int pop; /* 人口(population) */
    struct city *nextCity;
    struct city *nextCityinCountry;
}city;

typedef struct cities{
    struct cities *preCityNode;
    city *this;
    struct cities *nextCityNode;
}cities;

typedef struct cityList{
    cities *head;
    cities *end;
    cities *current;
}cityList;

// List function
void insertEnd(cities *newNode,cityList *list){
        newNode -> preCityNode = list -> end; 
        list -> end -> nextCityNode = newNode;
        list -> end = newNode;
}

void insertHead(cities *newNode,cityList *list){
    newNode -> nextCityNode = list -> head;    
    list -> head -> preCityNode = newNode;
    list -> head = newNode;
    return;
}

void insertLeft(cities *newNode,cities *currentNode){
    //modify now node
    newNode -> preCityNode = currentNode -> preCityNode;
    newNode -> nextCityNode = currentNode;
    //modify pre
    currentNode -> preCityNode -> nextCityNode = newNode;
    //modify next
    currentNode -> preCityNode = newNode;
    return;
}

void free_cityList(cityList *list) {
    if (list == NULL) {
        return; 
    }
    cities *current = list->head;
    cities *next;
    while (current != NULL) {
        next = current-> nextCityNode; 
        free(current);
        current = next; 
    }
    free(list);
}

//Node function
double getValue(cities* node, int n) {
    if (node == NULL || node->this == NULL) {
        return 0.0;
    }

    switch (n) {
        case 0:  
            return (double)node->this->pop;
        case 1:  
            return (double)node->this->lat;
        case 2:  
            return (double)node->this->lng;
        default: 
            return (double)node->this->pop;
    }
};

//sort from small to big
void sortAdd(cities *newCitiNode,cityList *sortedCity,int n){
    if(sortedCity -> head == NULL){
        sortedCity -> current = newCitiNode;
        sortedCity -> head = newCitiNode;
        sortedCity -> end  = newCitiNode;
    }

    double new = getValue(newCitiNode, n);
    double first = getValue(sortedCity -> head, n);
    double end = getValue(sortedCity -> end, n);
    
    // new is the smallest case
    if(new <= first){
        insertHead(newCitiNode,sortedCity);
        return;
    }
    // new is the biggest case
    if(new > end){
        insertEnd(newCitiNode,sortedCity);
        return;
    }
    // new is between case
    cities *temp = sortedCity -> head;
    double now = getValue(temp, n);
    //find the First node bigger than new
    while (now < new){ 
        temp = temp -> nextCityNode;
        now = getValue(temp, n);
    }
    // insert to left
    if(temp != NULL){ 
        //new is smaller than now => add to left
        insertLeft(newCitiNode, temp);
        return;
    }
};

void print(city *now){
        printf("City Name:%s, lat:%f lng:%f [%s] Population:%d\n",now -> cityName, now -> lat, now -> lng,
        now -> countryName, now -> pop);
}

/*
Use the FNV-1a hash algorithm
refrence link: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function

input: string to be hashed
return: hash value to this input srting
*/
unsigned int hash(char *str){
    int hash = FNVOffsetBasis;
    for(int i = 0; i < strlen(str); i++){
        hash ^= (unsigned int) str[i];
        hash *= FNVPrime;
    }
    return hash;
}

/*
Function: add a city information to the city name base hashtable and country name base hashtable
if there is another value of city had the same hash key, will add to the head of hashtable

input: cityname, lat, lng, contryname, pop
return: null
*/
void add(char *cityName, float lat, float lng, char *countryName,int pop){
    int cityHashkey = hash(cityName) % HASHSIZE;
    int countryHashkey = hash(countryName) % HASHSIZE;
    //debug
    //printf("test:%s,%d,%d\n", cityName, cityHashkey,countryHashkey);
    city *newcity;
    newcity = malloc(sizeof(struct city));
    newcity -> cityName = malloc(strlen(cityName) + 1);
    strcpy(newcity -> cityName, cityName);
    newcity -> countryName = malloc(strlen(countryName) + 1);
    strcpy(newcity -> countryName, countryName);
    newcity -> lat = lat;
    newcity -> lng = lng;
    newcity -> pop = pop;
    newcity -> nextCity = cityHashtable[cityHashkey]; 
    cityHashtable[cityHashkey] = newcity;
    cityTableLoad[cityHashkey] ++;
    newcity -> nextCityinCountry = countryHashtable[countryHashkey];
    countryHashtable[countryHashkey] = newcity;
}

void free_all_memory() {
    for (int i = 0; i < HASHSIZE; i++) {
        city *current = cityHashtable[i];
        city *next;
        while (current != NULL) {
            next = current->nextCity; 
            free(current->cityName);
            free(current->countryName);
            free(current);
            current = next; 
        }
        cityHashtable[i] = NULL;
    }
}

/*
Check and print how many elements in each table and the loadFactor;
TODO: change to global var to optmas
*/
void dist(){
    printf("--HASHSIZE: %d--", HASHSIZE);
    float numberOfElement = 0;
    for(int i = 0; i < HASHSIZE; i++){
        printf("Table[%d]:%d\n", i, cityTableLoad[i]);
        numberOfElement += cityTableLoad[i];
    }
    float loadFactor = numberOfElement / HASHSIZE;
    printf("HashLoadFactor:%.2f\n", loadFactor);
    return;
}

/*
search function_1 : input a name of city and show the other info

input: city name to search
output: all information about this country
*/
void print_city(char *cityName){
    int cityHashkey = hash(cityName) % HASHSIZE;
    city *now = cityHashtable[cityHashkey];
     while (now != NULL && strcmp(now->cityName, cityName) != 0) {
        now = now->nextCity; 
    }
    if (now != NULL) {
        print(now);
    } else {
        printf("No such city named: %s\n", cityName);
    }
    return;
}

/*
Make a city list in the input country by upscale order with specify data

input: country name, data type : 0 = pop, 1 = lat, 2 = lng
return: sorted list
*/
cityList* sort_cities(char *countryName, int dataType){
    int cityHashkey = hash(countryName) % HASHSIZE; //find buscket
    city *nowCity = countryHashtable[cityHashkey]; 

    //ini sortcitylist
    cityList *sortedCity = malloc(sizeof(cityList)); 
    sortedCity -> current = NULL;
    sortedCity -> head = NULL;
    sortedCity -> end = NULL;

    while (nowCity != NULL)
    { 
        if(strcmp(nowCity -> countryName, countryName) == 0){  //if nowcity is in this country
            //TODO : creaate a new citynode
            cities *newCitiNode = malloc(sizeof(cities));
            newCitiNode -> this = nowCity;
            newCitiNode -> preCityNode = NULL;
            newCitiNode -> nextCityNode = NULL;
            // add new citynode to sorted list

            sortAdd(newCitiNode, sortedCity, dataType); //sort by list
        }
        nowCity = nowCity -> nextCityinCountry;
    }

    return sortedCity;
}

//qs4 search function_2 : input a name of country and show all the city in this country by people
void print_cities(char *countryName){
    cityList *sortedCity = sort_cities(countryName, 0); //sort by 0 = pop
    if (sortedCity == NULL || sortedCity->head == NULL) {
        printf("No cities found for country: %s\n", countryName);
        if (sortedCity != NULL) {
            free_cityList(sortedCity);
        }
        return;
    }

    sortedCity -> current = sortedCity -> end;
    while (sortedCity -> current != NULL){
        printf("test");
        print(sortedCity -> current -> this);
        sortedCity -> current = sortedCity -> current -> preCityNode;
    }
    return ;
    free_cityList(sortedCity);
}


//qs5 search function_3 : custom the input and show info as the commend way
//人口順(0) or 緯度順(1) or 経度順の指定(2)と，昇順(0)or降順(1)の指定と表示開始都市名を引数に追加し，指定された並びで都市を表示できるように変更したprint_cities2()を作成せよ．
//例: print_cities2("Japan", 0, 1, "Noda"); この場合はNodaより人口が少ない日本の都市をNodaから順に表示する．
void print_cities2(char *countryName, int dataType, int order, char *startCity){
    cityList *sortedCity = sort_cities(countryName, dataType); 

    if (sortedCity == NULL || sortedCity->head == NULL) {
        printf("No cities found for country: %s\n", countryName);
        if (sortedCity != NULL) {
            free_cityList(sortedCity); 
        }
        return;
    }

    //find startNode
    cities *startNode = NULL;
    if(startCity == NULL || strcmp(startCity, "0") == 0){
        if(order == 0){
            startNode = sortedCity -> head;
        }else{
            startNode = sortedCity -> end;
        }
    }else{
        cities *curNode = sortedCity -> head;
        while (curNode != NULL){         
            if(strcmp(curNode -> this -> cityName, startCity) == 0){
                startNode = curNode;
                break;
            }
            char *str = curNode-> this -> cityName;
            curNode = curNode -> nextCityNode;
        }
    }

    //print by order
    if(startNode == NULL){
        printf("No such city named:%s\n", startCity);
    }else{
        cities *current = startNode;
        if(order == 0){// small to big
            while (current != NULL){
                print(current -> this);
                current = current -> nextCityNode;
            }
        }else if(order == 1){// big to small
            while (current != NULL){
                print(current -> this);
                current = current -> preCityNode;
            }
        }else{
            printf("order error\n");
        }
    }
    free_cityList(sortedCity);
    return ;
}

//sys opreat info
void sysMenuJp(){
    printf("===========================\n");
    printf("数字を入力して、プログラムを起動する.\n");
    printf("[1] ハッシュテーブルの分布を示す\n");
    printf("[2] 都市の情報を示す\n");
    printf("[3] 国に存在する都市を示す\n");
    printf("[4] 国に存在する都市を指定の形式で示す\n");
    printf("EOFを入力するプログラムを閉じる\n");
    printf("===========================\n");
    return;
}

int main(){
    struct timespec start, end;
    long long elapsed_ns;
    double elapsed_ms;
    
    char name[1024];
    char country[1024];
    float lat, lng;
    int pop, i, f;
    char *filename = "worldcities.txt";
    FILE *fp;

    for(int i = 0; i < HASHSIZE; i++){
        countryHashtable[i] = NULL;
        cityHashtable[i] = NULL;
        cityTableLoad[i] = 0;
    }
    fp = fopen(filename,"r");
    while((f = fscanf(fp,"%s %f %f %s %d",name,&lat,&lng,country,&pop))!=EOF){
        add(name, lat, lng, country, pop);
    }
    fclose(fp);
    sysMenuJp();
    char buffer[1024];
    int bufferint;
    while(1){
        int scanResult = scanf("%d", &bufferint);
        if(scanResult == EOF){
            printf("EOFを検出する、プログラムを閉じる\n");
            free_all_memory();
            break; 
        }else if (scanResult == 1){
            switch (bufferint){
                case 1:
                    dist();
                    break;
                case 2:
                    printf("探したいの都市は？\n");
                    scanf("%s", buffer);
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    print_city(buffer);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
                    elapsed_ms = elapsed_ns / 1000000.0;
                    printf("探す時間:  %.3f (ms)\n", elapsed_ms);
                    break;
                case 3:
                    printf("探したいの国は？\n");
                    scanf("%s", buffer);
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    print_cities(buffer);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
                    elapsed_ms = elapsed_ns / 1000000.0;
                    printf("探す時間:  %.3f (ms)\n", elapsed_ms);
                    break;
                case 4:
                    int dataType,order;
                    char cityName[1024] = "";
                    printf("探したい国の名前は？\n");
                    scanf("%s", buffer);
                    printf("並びたい順番を選択してください：\n[0]人口\n[1]緯度\n[2]経度\n");                    
                    scanf("%d", &dataType);
                    while (dataType != 1 && dataType != 2 && dataType != 0)
                    {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);    
                        printf("入力が間違います、再度に入力してください\n");
                        printf("並びたい順番を選択してください：\n[0]人口\n[1]緯度\n[2]経度\n");
                        scanf("%d", &dataType);
                    }
                    printf("並び順番を選択してください：\n[0]昇順\n[1]降順\n");
                    scanf("%d", &order);
                    while (order != 1  && order != 0)
                    {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("入力が間違います、再度に入力してください\n");
                        printf("並びたい順番を選択してください：\n[0]人口\n[1]緯度\n[2]経度\n");
                        scanf("%d", &order);
                    }
                    printf("開始したいの都市ファイルを入力くださ（指定しないのときを0を入力して、すべての都市が表示する）：\n");
                    scanf("%s", cityName);
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    print_cities2(buffer, dataType, order,cityName);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
                    elapsed_ms = elapsed_ns / 1000000.0;
                    printf("探す時間:  %.3f (ms)\n", elapsed_ms);
                    break;
                default:
                    printf("入力が間違います、再度に入力してください。\n");
                    break;
                }   
            }else{
            printf("入力が間違います、再度に入力してください。\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        sysMenuJp();
    }
    return 0;
}

