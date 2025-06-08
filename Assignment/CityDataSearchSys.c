#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void sortAdd(cities *newCitiNode,cityList *sortedCity,int n){
    if(sortedCity -> head == NULL){
        sortedCity -> current = newCitiNode;
        sortedCity -> head = newCitiNode;
        sortedCity -> end  = newCitiNode;
    }

    double new = getValue(newCitiNode, n);
    double first = getValue(sortedCity -> head, n);
    double end = getValue(sortedCity -> end, n);

    if(new <= first){// new is the smallest
        newCitiNode -> nextCityNode = sortedCity -> head;    
        
        sortedCity -> head -> preCityNode = newCitiNode;
        sortedCity -> head = newCitiNode;
        return;

    }

    if(new > end){
        newCitiNode -> preCityNode = sortedCity -> end; 
        
        sortedCity -> end -> nextCityNode = newCitiNode;
        sortedCity -> end = newCitiNode;
        return;
    }
    //printf("new: %d\n", new);
    cities *temp = sortedCity -> head;
    double now = getValue(temp, n);
    while (now < new)
    {
        temp = temp -> nextCityNode;
        now = getValue(temp, n);


    }
    //printf("now: %d\n", now);
    if(temp != NULL){
        //printf("test2\n");
        //new is smaller than now => add to left
        //modify now node
        newCitiNode -> preCityNode = temp -> preCityNode;
        newCitiNode -> nextCityNode = temp;
        //modify pre
        temp -> preCityNode -> nextCityNode = newCitiNode;
        //modify next
        temp -> preCityNode = newCitiNode;
        return;

    }
};

void addCitiesLeft(cities *nowCities, city *nowCity, cities *firstCities){
    cities *newCities = malloc(sizeof(cities));
    newCities -> preCityNode = nowCities -> preCityNode;

    newCities -> this = nowCity;

    newCities -> nextCityNode = nowCities;

    nowCities -> preCityNode = newCities;
    
    if(newCities -> preCityNode != NULL){
        newCities -> preCityNode -> nextCityNode = newCities;
    }else{
        firstCities = newCities;
    }
    return;
}

void addCitiesRight(cities *nowCities, city *nowCity, cities *lastCities){
    cities *newCities = malloc(sizeof(cities));
    newCities -> nextCityNode = nowCities -> nextCityNode;
    newCities -> this = nowCity;
    newCities -> preCityNode = nowCities;

    nowCities -> nextCityNode = newCities;
    if(newCities -> nextCityNode != NULL){
        newCities -> preCityNode -> nextCityNode = newCities;
    }else{
        lastCities = newCities;
    }
    return;
}

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

/*
Check and print how many elements in each table and the loadFactor;
TODO: change to global var to optmas
*/
void dist(){
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
    
    while(strcmp(now -> cityName, cityName) != 0){
        if(now -> nextCity == NULL){
            printf("No such city name is:%s\n",cityName);
            return;
        }
        now = now -> nextCity;
    }
    printf("City Name:%s, lat:%f lng:%f [%s] Population:%d\n",now -> cityName, now -> lat, now -> lng,
        now -> countryName, now -> pop);
    return;
    
}

cityList* sort_cities(char *countryName, int dataType){
    int cityHashkey = hash(countryName) % HASHSIZE; //find buscket
    city *nowCity = countryHashtable[cityHashkey]; 

    //ini sortcitylist
    cityList *sortedCity = malloc(sizeof(cityList)); 
    sortedCity -> current = NULL;
    sortedCity -> head = NULL;
    sortedCity -> end = NULL;
    
    while (nowCity -> nextCityinCountry != NULL)
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
//qs4 TODO::search function_2 : input a name of country and show all the city in this country by people
void print_cities(char *countryName){
    cityList *sortedCity = sort_cities(countryName, 0); //sort by 0 = pop
    sortedCity -> current = sortedCity -> end;
    while (sortedCity -> current != NULL){
        print(sortedCity -> current -> this);
        sortedCity -> current = sortedCity -> current -> preCityNode;
    }
    return ;
    //TODO free;
}


//qs5 TODO::search function_3 : custom the input and show info as the commend way
//人口順(0) or 緯度順(1) or 経度順の指定(2)と，昇順(0)or降順(1)の指定と表示開始都市名を引数に追加し，指定された並びで都市を表示できるように変更したprint_cities2()を作成せよ．
//例: print_cities2("Japan", 0, 1, "Noda"); この場合はNodaより人口が少ない日本の都市をNodaから順に表示する．
void print_cities2(char *countryName, int dataType, int order, char *startCity){
    cityList *sortedCity = sort_cities(countryName, dataType); 

    if (sortedCity == NULL || sortedCity->head == NULL) {
        printf("No cities found for country: %s\n", countryName);
        if (sortedCity != NULL) {
            //TODO : free_cityList(sortedCity); 
        }
        return;
    }

    //find startNode
    cities *startNode = NULL;

    if(startCity == NULL || strcmp(startCity, "") == 0){
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

            curNode = curNode -> nextCityNode;
        }

    }

    //print by order
    if(startNode == NULL){
        printf("startNode error\n");
    }else{
        cities *current = startNode;

        if(order == 0){
            while (current != NULL){
                print(current -> this);
                current = current -> nextCityNode;
            }
        }else if(order == 1){
            while (current != NULL){
                print(current -> this);
                current = current -> preCityNode;
            }
        }else{
            printf("order error\n");
        }
    }
    return ;
}

//sys opreat info
void sysMenuJp(){
    printf("===========================");
    printf("[1] ファイルを読み込み");
    printf("[2] show the discribe of Hashtable");
    printf("[3] search the city info");
    printf("[4] ");
}
void sysMenuEn(){
    printf("===========================");
    printf("[1] read file");
    printf("[2] show the discribe of Hashtable");
    printf("[3] search the city info");
    printf("[4] ");
}


int main(){
    char name[1024];
    char country[1024];
    float lat, lng;
    int pop, i, f;
    char *filename = "worldcities.txt";
    FILE *fp;
    char buffer[1024];
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
    dist();
    //printf("City name? ");
    //scanf("%s", buffer);
    //print_cities("Japan"); 
    //char inputBuffer[1024];
    //print_cities2("China", 0, 1, "Chongqing");


    //TODO::trans to hashtable


    //TODO::get input
    




    //printf("Country name? ");
    //scanf("%s", buffer);
    //print_cities(buffer);

    return 0;
}

