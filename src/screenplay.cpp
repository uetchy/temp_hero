#include "screenplay.hpp"

void printTitle() {
  iprint(50, {
    "\n",
    "\n",
    "\n",
    "\n",
    "\n",
    "\n",
    "                            ll 　 ll 　      　　 lll　 　 　 　 　 　 　              \n",
    "                            ll,,,,ll　ll''''''ll,　ll ,,l''' ,,ll'''''ll,　 l,''''''ll,\n" ,
    "                            ll 　 ll ,,lll'''''lll lll''ll,,　ll''''''''''' lll 　  ll\n" ,
    "                            ll 　 ll 'll,,,,,l'lll lll　''ll, 'll,,,,,,l''  lll 　  ll \n",
    "\n",
    "\n",
    "                    'll,, ,ll''\n",
    "                    ''ll,ll''　,ll 　   ll lll   　 ll    ,ll''''''ll,   ll, ,ll'   ll''''''ll, \n",
    "                       ll　　   ll 　   ll lll 　   ll　   ''''llll,,　   ll,,ll'  ,,,ll'''''lll \n",
    "                       ll' 　　 ll,,,,,l'l　ll,,,,,'ll'  'll,,,,,,l''　  'lll'　    'll,,,,,,'lll\n",
    "                                         　　                        　,,,ll'\n",
    "\n",
    "\n",
    "\n",
    "\n",
    "\n",
    "\n",
    "\n"
  });
}

void printRulesEN() {
  iprint(100, {
    "\nRules of Hakken Yuusha:\n",
    "==========================\n" ,
    "1) You are a hero that was summoned inside of a dungeon\n" ,
    "2) You need to get out from the dungeon to save the world\n" ,
    "3) But since the path lead to the  outside is blocked by rocks\n" ,
    "4) You need to get a shovels that the boss use as a weapon\n" ,
    "5) There are more than 1 boss\n" ,
    "6) Defeating the hidden boss will improve your chances of winning\n" ,
    "7) In the fight, you can attack different part of the enemies and one of them is their weak point\n" ,
    "8) Each enemies have different weak point\n" ,
    "9) Attacking the weak point will deal bigger damage to the enemies\n" ,
    "10) There are tons of hint inside the dungeon left by some other adventurers\n" ,
    "11) Some of the hint are useful, but some are not .\n" ,
    "12) Every time you move or read a hint, the encount gauge will fill up\n" ,
    "13) After the encount gauge is filled to a certain point, you will be force to fight\n" ,
    "14) You can heal yourself by using potion found in the dungeon\n" ,
    "15) The potion will heal you back to full health when used outside of battle\n" ,
    "16) Or heal for 10 HP when used in battle\n" ,
    "17) Using potion when battling will use your turn, so you can't use potion and attack at the same time\n" ,
    "Good luck with your quest to escape the dungeon\n"
  });
}

void printRulesJP() {
  iprint(100, {
    "\n派遣勇者のルール:\n",
    "==========================\n" ,
    "01) プレイヤーはダンジョンの中に召喚された勇者です\n" ,
    "02) プレイヤーはこのダンジョンから脱出し、世界を救わなければいけません\n" ,
    "03) しかしこのダンジョンの出口は岩で塞がれています\n" ,
    "04) その岩を壊すために、ダンジョンボースに武器として使われているシャベルが必要です\n" ,
    "05)　このダンジョンではボス１つ以上います\n" ,
    "06) その裏ボスを倒すとプレイヤーはパワーアップし、ダンジョンから脱出可能性がもっと広がる\n" ,
    "07) 敵（雑魚とボス）は複数の部位を持ち、その中に１つの弱点部位がいます\n" ,
    "08) 敵の種類による、弱点部位は変わります\n" ,
    "09) 弱点部位に攻撃すると、敵に大ダメージを与えることができます\n" ,
    "10) ダンジョン内には以前冒険した冒険者のヒントがたくさんあります\n" ,
    "11) そのヒントは大事なヒントだけではなく、意味不明のヒントもあります\n" ,
    "12) プレイヤーは動くたびにとヒントを見るときエンカウントゲージが１つたまります\n" ,
    "13) エンカウントゲージが溜まると、強制に敵と戦うことになります\n" ,
    "12) ダンジョン内に見つかったポションはマップ中に使うと全回することになりますが、\n" ,
    "13) 戦闘中に使うと、HPが１０しか回復しません\n" ,
    "14) 戦闘中にポションを使うと自分のターンが使うため、そのターンに敵を攻撃することができません\n" ,
    "X) まだ完成していません\n" ,
    "X) もっと詳しいルールは英語の方に書かれてあります\n",
    "では。。。健闘を祈る\n"
  });
}
