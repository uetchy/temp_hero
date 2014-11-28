# 派遣勇者

```
                      - T e m p o r a r y  H e r o -
  ___ ___         __                _____.___.                  .__
 /   |   \_____  |  | __ ____   ____\__  |   |__ __ __ __  _____|  |__ _____
/    ~    \__  \ |  |/ // __ \ /    \/   |   |  |  \  |  \/  ___/  |  \\__  \
\    Y    // __ \|    <\  ___/|   |  \____   |  |  /  |  /\___ \|   Y  \/ __ \_
 \___|_  /(____  /__|_ \\___  >___|  / ______|____/|____//____  >___|  (____  /
       \/      \/     \/    \/     \/\/                       \/     \/     \/
```

## How to Compile

### Manually compile

gccを使ってコンパイルする。例えば、`gcc battle.c`などのようにする。

```session
$ gcc <コンパイルするCファイル>
$ ./a.out
```

### Compile automatically

以下のコマンドで__main.c__をコンパイルして実行することが出来ます。これには、__Automake__と__Autoconf__が必要です。

```session
$ ./bootstrap
$ ./configure
$ make
$ ./src/main
```

#### Clean

以下のコマンドでクリーニング

```session
$ make maintainer-clean
```

## 構造体の仕様

### Monster関係

```c
[00][01][02][03]
[10][11][12][13]
[20][21][22][23]
[30][31][32][33]

monsters = [
    [
        "Iida monster", // Monster name
        10000, // HP
        10000, // Attack power
        "---", // Ascii art
        [ // Parts
            ["Head", true],
            ["Stomach", false],
            ["Tail", false]
        ]
    ],
    [
        "Iida monster", // Monster name
        10000, // HP
        10000, // Attack power
        "---", // Ascii art
        [ // Weakpoint
            ["Head", true],
            ["Stomach", false],
            ["Tail", false]
        ]
    ]
]
```
