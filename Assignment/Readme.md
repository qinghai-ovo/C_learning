# レポート課題(2025)

## 課題概要  

以下の都市データを用いて，後述する実装の項目で指定された関数を記述したプログラムを作成せよ．

## 使用データ  

課題で使用するデータは以下の世界の都市データ(約43,000件)を用いる．
ダウンロードして使用すること．

データは  
> " 都市名 緯度　経度　国名　人口 "

の順で，1都市の情報が1列に記載されている．人口が不明の都市は-1の値が入っているため，データの欠損は考慮しなくてよい．
>例  
>Tokyo   35.6839 139.7744          >Japan   39105000  

## 使用する構造体

構造体は以下を用いること.

```c
struct city{
　char *name; /* 都市名 */
　float lat; /* 緯度 */
　float lng; /* 経度 */
　char *country; /* 国名 */
　int pop; /* 人口(population) */
};
```

## 実装

1. 都市データファイルからデータを読み込み，リスト構造を用いてデータを作成する関数 add(引数:都市名，緯度，経度，国名，人口) を作成せよ． ただし，city構造体のデータは，ハッシュテーブルを用いて探索を効率化すること．また必要に応じて構造体のメンバにポインタ変数を適宜入れること．
2. 作成したハッシュテーブルの分布を調べる関数 dist()を作成せよ．また可能であれば dist()の結果を元に，偏りの少ないハッシュ関数を自作せよ．
3. 標準入力より都市名を入力すると，都市の名前，緯度，経度，国名，人口を表示する関数 print_city(引数:都市名) を作成せよ.  
    > 例: print_city("Noda");
4. 国名を指定し，その国に存在する都市名を人口順(多い順)に表示する関数 print_cities(引数:国名) を作成せよ．
    > 例: print_cities("Japan");

5. (任意課題)　print_cities()を拡張して，人口順(0) or 緯度順(1) or 経度順の指定(2)と，昇順(0)or降順(1)の指定と表示開始都市名を引数に追加し，指定された並びで都市を表示できるように変更したprint_cities2()を作成せよ．
    > 例: print_cities2("Japan", 0, 1, "Noda"); この場合はNodaより人口が少ない日本の都市をNodaから順に表示する．

## main関数

main関数は以下を用いて良い．（用いなくても良い & 改変も自由)

```c
int main(){
  char name[1024];
  char country[1024];
  float lat, lng;
  int pop, i, f;
  char *filename = "worldcities.txt";
  FILE *fp;
  char buffer[1024];
/*  任意課題用
  char buffer2[1024];
  int n, m;  
*/
    
  for(i=0; i<HASHSIZE; i++){
    hashtable[i]=NULL;
  }
  fp = fopen(filename,"r");
  while((f = fscanf(fp,"%s %f %f %s %d",name,&lat,&lng,country,&pop))!=EOF){
    add(name, lat, lng, country, pop);
  }
  fclose(fp);
  dist();

  printf("City name? ");
  scanf("%s", buffer);
  print_city(buffer); 

  printf("Country name? ");
  scanf("%s", buffer);
  print_cities(buffer);

/* 任意課題テスト用
  printf("Optional input? ");
  scanf("%s %d %d %s", buffer, &n, &m, buffer2);
  print_cities2(buffer, n, m, buffer2);
*/
}
```

## 実行例

```text
$ ./a.out
--HASHSIZE: 101-- ← dist()の結果ここから
TABLE[0]:446
TABLE[1]:403
TABLE[2]:430
TABLE[3]:393
TABLE[4]:448
TABLE[5]:424
TABLE[6]:435
TABLE[7]:432

〜中略〜

TABLE[92]:398
TABLE[93]:453
TABLE[94]:439
TABLE[95]:406
TABLE[96]:444
TABLE[97]:431
TABLE[98]:451
TABLE[99]:431
TABLE[100]:419
---------------- ← dist()の結果ここまで
City name? Noda  ←標準入力
City Name:Noda lat:35.955002 lng:139.874695 [Japan] Population:152227  ← print_city()の結果
Country name? Japan ←標準入力
[Japan cities]  ← print_cities()の結果ここから ※緯度経度は省いているが表示しても良い
Tokyo [Japan] 39105000
Osaka [Japan] 15490000
Nagoya [Japan] 9522000
Yokohama [Japan] 3757630
Fukuoka [Japan] 2280000
Sapporo [Japan] 1961690
Kawasaki [Japan] 1539522
Kobe [Japan] 1513193
Kyoto [Japan] 1464890
Saitama [Japan] 1320571
Hiroshima [Japan] 1198021
Sendai [Japan] 1058070
Chiba [Japan] 981738
Setagaya [Japan] 940509
Kitakyushu [Japan] 935084
Sakai [Japan] 823523
Niigata [Japan] 790646
Hamamatsu [Japan] 788211
Nerima [Japan] 742463
Kumamoto [Japan] 738385
Ota-ku [Japan] 737187
Sagamihara [Japan] 722973
Okayama [Japan] 720043
Edogawa [Japan] 690457
Shizuoka [Japan] 685589
Adachi [Japan] 682326
Honcho [Japan] 641499
Kagoshima [Japan] 593754

〜中略〜

Ginoza [Japan] 5900
Shintoku [Japan] 5834
Tatsugo [Japan] 5753
Ohira [Japan] 5739
Takamori [Japan] 5724
China [Japan] 5686
Hamanaka-sakuraminami [Japan] 5674
Kozaki [Japan] 5663
Onagawa [Japan] 5662
Kuzumaki [Japan] 5467
Amagi [Japan] 5465
Taiki [Japan] 5449
Hachirougata [Japan] 5445
Takae [Japan] 5395
Asuka [Japan] 5241
Naie [Japan] 5235
Yamanaka [Japan] 5170
Shibetsu [Japan] 5123
Oshamambe [Japan] 5112
Ochi [Japan] 5111
Imagane [Japan] 5052
Kaneyama [Japan] 5045
Naganohara [Japan] 5026 ← print_cities()の結果ここまで


任意課題実行例

[Japan Population Ranking(UP), Yokohama start] ← print_cities2("Japan", 0, 0, "Yokohama");の結果
   1. Yokohama [Japan] 35.433300 139.633301 3757630
   2. Nagoya [Japan] 35.116699 136.933304 9522000
   3. Osaka [Japan] 34.751999 135.458206 15490000
   4. Tokyo [Japan] 35.683899 139.774399 39105000

[Japan Longitude Ranking(DOWN), Naha start] ← print_cities2("Japan", 2, 1, "Naha");の結果
   1. Naha [Japan] 26.212200 127.678902 316048
   2. Miyakojima [Japan] 24.805599 125.281097 52390
   3. Ishigaki [Japan] 24.333300 124.150002 48258

[Japan Latitude Ranking(UP), Abashiri start] ← print_cities2("Japan", 1, 0, "Abashiri");の結果
   1. Abashiri [Japan] 44.020599 144.273605 34640
   2. Mukaiengaru [Japan] 44.061699 143.528107 19358
   3. Minamishibetsucho [Japan] 44.178600 142.400604 18138
   4. Nayoro [Japan] 44.355801 142.463303 27062
   5. Mobetsu [Japan] 44.356400 143.354202 21317
   6. Wakabadai [Japan] 45.400002 141.699997 33036
   ```

## ヒント

- プログラム冒頭に 「#define HASHSIZE 101」と記述しておくと，コンパイル前にプログラム中の「HASHSIZE」という文字列は「101」に置き換えられてコンパイルされる．ハッシュテーブルのサイズを変更する場合には #defineを用いると，この行のみの変更で済む．
- 昇順・降順は，双方向リストや2分木の構造を検討すると良い．

## 考察ネタ

- ハッシュ関数の作り方にもよるが，ハッシュテーブルのサイズは素数が良いと言われている．その理由などを考察に書けると良い．（離散数学等の講義が参考になるかもしれない）.  
- dist関数の結果を元に，偏りの少ないハッシュ関数について考察すると良い．
- 想定される検索に応じてデータ構造を工夫した点，または検索時に工夫した点なども考察に取り入れると良い．
- 検索にかかるコスト(実時間でも良いが，計算機性能によっては一瞬なので，結果を表示するまでに閲覧したcityデータの数)を算出して考察材料にすると良い.