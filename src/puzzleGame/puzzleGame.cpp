#include <iostream>
using namespace std;

const char gStageData[] = "\
    □□□□□□□□\n\
    □ ..p  □\n\
    □ oo   □\n\
    □      □\n\
    □□□□□□□□"
    ;

const int gStageWidth   =8;
const int gStageHeight  =5;

enum Object
{
    OBJ_SPACE,
    OBJ_WALL,
    OBJ_GOAL,
    OBJ_BLOCK,
    OBJ_BLOCK_ON_GOAL,
    OBJ_MAN,
    OBJ_MAN_ON_GOAL,

    OBJ_UNKNOWN,
};

void initialize(Object *state, int width, int height, const char *stageData){
    const char *d =stageData; //읽기용 포인터
    int         x =0;
    int         y =0;
    while(*d != '\0'){
        Object t;
        switch(*d){
            case '□': t =OBJ_WALL;           break;
            case ' ': t =OBJ_SPACE;          break;
            case 'o': t =OBJ_BLOCK;          break;
            case 'O': t =OBJ_BLOCK_ON_GOAL;  break;
            case '.': t =OBJ_GOAL;           break;
            case 'p': t =OBJ_MAN;            break;
            case 'P': t =OBJ_MAN_ON_GOAL;    break;
            case '\n':
                x =0;
                ++y;
                t =OBJ_UNKNOWN;
                break;
            default: t =OBJ_UNKNOWN; break;
        }
        ++d;
        // not OBJ_UNKNOWN => 쓰기
        if(t != OBJ_UNKNOWN){
            state[y * width + x] =t;
            ++x;
        }
    }
};
void draw       (const Object *state, int width, int height);
void update     (Object *state, char input, int width, int height);
bool checkClear (const Object *state, int width, int height);

int main()
{
    //상태 배열확보
    Object *state = new Object[gStageWidth * gStageHeight];
    //스테이지 초기화
    initialize(state, gStageWidth, gStageHeight, gStageData);
    //메인루프
    while (true)
    {
        //화면 그리기
        draw(state, gStageWidth, gStageHeight);
        //클리어 체크
        if (checkClear(state, gStageWidth, gStageHeight))
        {
            break; //클리어체크
        }
        //입력값 얻기
        cout << "a is Left, s is Right, w is Up, z is Down. command?" << endl; //조작설명
        char input;
        cin >> input;
        //갱신
        update(state, input, gStageWidth, gStageHeight);
    }
    //축하메시지
    cout << "Congratulation's You Win!" << endl;
    //뒷정리
    delete[] state;
    state = 0;

    return 0;
}
