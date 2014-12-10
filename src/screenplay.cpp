#include <stdio.h>
#include <ncurses.h>

void printTitle() {
  printw("\n\n\n\n\n\n\n");
  printw("                    ll 　 ll 　      　　 lll　 　 　 　 　 　 　              \n");
  printw("                    ll,,,,ll　ll''''''ll,　ll ,,l''' ,,ll'''''ll,　 l,''''''ll,\n" );
  printw("                    ll 　 ll ,,lll'''''lll lll''ll,,　ll''''''''''' lll 　  ll\n" );
  printw("                    ll 　 ll 'll,,,,,l'lll lll　''ll, 'll,,,,,,l''  lll 　  ll \n");
  printw("                    \n");
  printw("                    \n");
  printw("                    'll,, ,ll''\n");
  printw("                    ''ll,ll''　,ll 　   ll lll   　 ll    ,ll''''''ll,   ll, ,ll'   ll''''''ll, \n");
  printw("                       ll　　   ll 　   ll lll 　   ll　   ''''llll,,　   ll,,ll'  ,,,ll'''''lll \n");
  printw("                       ll' 　　 ll,,,,,l'l　ll,,,,,'ll'  'll,,,,,,l''　  'lll'　    'll,,,,,,'lll\n");
  printw("                                         　　                        　,,,ll'\n");
}

void printRulesEN() {
  printw( "\nRules of Hakken Yuusha:\n");
  printw( "==========================\n" );
  printw( "1) You are a hero that was summoned inside of a dungeon\n" );
  printw( "2) You need to get out from the dungeon to save the world\n" );
  printw( "3) But since the path lead to the  outside is blocked by rocks\n" );
  printw( "4) You need to get a shovels that the boss use as a weapon\n" );
  printw( "5) There are more than 1 boss\n" );
  printw( "6) Defeating the hidden boss will improve your chances of winning\n" );
  printw( "7) In the fight, you can attack different part of the enemies and one of them is their weak point\n" );
  printw( "8) Each enemies have different weak point\n" );
  printw( "9) Attacking the weak point will deal bigger damage to the enemies\n" );
  printw( "10) There are tons of hint inside the dungeon left by some other adventurers\n" );
  printw( "11) Some of the hint are useful, but some are not .\n" );
  printw( "12) Every time you move or read a hint, the encount gauge will fill up\n" );
  printw( "13) After the encount gauge is filled to a certain point, you will be force to fight\n" );
  printw( "14) You can heal yourself by using potion found in the dungeon\n" );
  printw( "15) The potion will heal you back to full health when used outside of battle\n" );
  printw( "16) Or heal for 10 HP when used in battle\n" );
  printw( "17) Using potion when battling will use your turn, so you can't use potion and attack at the same time\n" );

  printw( "Good luck with your quest to escape the dungeon\n" );
}

void printRulesJP() {
  printw( "\n派遣勇者のルール:\n");
  printw( "==========================\n" );
  printw( "01) プレイヤーはダンジョンの中に召喚された勇者です\n" );
  printw( "02) プレイヤーはこのダンジョンから脱出し、世界を救わなければいけません\n" );
  printw( "03) しかしこのダンジョンの出口は岩で塞がれています\n" );
  printw( "04) その岩を壊すために、ダンジョンボースに武器として使われているシャベルが必要です\n" );
  printw( "05)　このダンジョンではボス１つ以上います\n" );
  printw( "06) その裏ボスを倒すとプレイヤーはパワーアップし、ダンジョンから脱出可能性がもっと広がる\n" );
  printw( "07) 敵（雑魚とボス）は複数の部位を持ち、その中に１つの弱点部位がいます\n" );
  printw( "08) 敵の種類による、弱点部位は変わります\n" );
  printw( "09) 弱点部位に攻撃すると、敵に大ダメージを与えることができます\n" );
  printw( "10) ダンジョン内には以前冒険した冒険者のヒントがたくさんあります\n" );
  printw( "11) そのヒントは大事なヒントだけではなく、意味不明のヒントもあります\n" );
  printw( "12) プレイヤーは動くたびにとヒントを見るときエンカウントゲージが１つたまります\n" );
  printw( "13) エンカウントゲージが溜まると、強制に敵と戦うことになります\n" );
  printw( "12) ダンジョン内に見つかったポションはマップ中に使うと全回することになりますが、\n" );
  printw( "13) 戦闘中に使うと、HPが１０しか回復しません\n" );
  printw( "14) 戦闘中にポションを使うと自分のターンが使うため、そのターンに敵を攻撃することができません\n" );
  printw( "X) まだ完成していません\n" );
  printw( "X) もっと詳しいルールは英語の方に書かれてあります\n" );

  printw( "では。。。健闘を祈る\n" );
}
