/**
 * metric.h
 * 점이나 크기와 같은 규격들을 정의해놓았습니다.
 */

#ifndef metric_h
#define metric_h

#include "macros.h"

/**
 * 32비트 usigned 정수로부터 상위(X) / 하위(Y) 16비트를 꺼내옵니다.
 */
#define X(POINT)                UPPER16(POINT)
#define Y(POINT)                LOWER16(POINT)

/**
 * 32비트 usigned 정수로부터 상위(WIDTH) / 하위(HEIGHT) 16비트를 꺼내옵니다.
 */
#define WIDTH(SIZE)             UPPER16(SIZE)
#define HEIGHT(SIZE)            LOWER16(SIZE)

/**
 * 두 unsigned 16비트 정수를 하나의 unsigned 32비트 정수로 합칩니다.
 * 점과 크기를 위해 모두 사용할 수 있는데, 둘은 사실 같습니당.
 */
#define POINT(X, Y)             COMBINE16(X, Y)
#define SIZE(W, H)              COMBINE16(W, H)

/**
 * 두 점을 가지고, X방향 길이와 Y방향 길이를 구합니다.
 */
#define DELTA_X(P0, P1)     ABS(X(P1) - X(P0))
#define DELTA_Y(P0, P1)    ABS(Y(P1) - Y(P0))

/**
 * 두 점을 가지고, 가로 길이 차이와 세로 길이 차이를 구합니다.
 */
#define DELTA_WIDTH(P0, P1)     ABS(WIDTH(P1) - WIDTH(P0))
#define DELTA_HEIGHT(P0, P1)    ABS(HEIGHT(P1) - HEIGHT(P0))

/**
 * 정수 X가 START <= X <= END인지 검사합니다.
 */
#define IN_RANGE(X, START, END) ((X >= START) && (X <= END))

/**
 * 점을 표현하는 연결리스트에서 쓰일 노드.
 */
struct point_node {
    short x;
    short y;
    struct point_node *next;
};

/**
 * 연결리스트의 시작과 끝을 가지고 있는 '연결리스트' 그 자체.
 * 리스트를 가지고 다닐 때에는 이놈만 씁니당.
 */
struct points {
    struct point_node *head;
    
    /*
     * head만 가지고 다니면 될 것을, 굳이 새 구조체를 정의해서 이렇게 들고다니는 이유:
     *
     * 1. Node만 봐서는 이게 시작인지 끝인지도 몰라 이것을 연결리스트로 보기에는 대표성이 없습니다.
     * 2. 새 노드를 추가할 때 기존 리스트의 마지막 노드에 연결해야 하는데, 매번 head부터 끝까지 찾는 것은 낭비이므로,
     *  tail을 미리 가지고 있으면서 O(1) 시간 내에 추가 연산이 가능하도록 합니다.
     */
    struct point_node *tail;
};

void points_add(struct points *points, short x, short y);

void points_free(struct points *points);

#endif /* metric_h */
