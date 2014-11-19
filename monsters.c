struct Monster_Part {
  char name[256];  // 部位の名前
  int isWeak; // 弱点か
};

struct Monster {
  char name[256];
  int hp;
  int power;
  char aa[256];
  struct Monster_Part parts[5]; // TODO: 最大数を決めておく。もしくは数を可変にする方法を調べておく
};

Monster monsters[2];

void initMonsters() {
  monsters[0].name  = "Jiba-nyan";
  monsters[0].hp    = 100;
  monsters[0].power = 100;
  monsters[0].aa    = "ef";
  monsters[0].parts = {
    ["test", 0]
  };
}
