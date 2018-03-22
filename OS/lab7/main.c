#include <stdio.h>
struct Foo {
        int a,b;
        int (*add)();
};
int add(struct Foo *this){
        return this->a+this->b;
}

int main(){
        struct Foo obj= {3,4,add};
        printf("%d\n", obj.add(&obj));
}
