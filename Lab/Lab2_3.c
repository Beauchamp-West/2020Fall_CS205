#include <stdio.h>
int main(){
    char a;
    int b;
    float c;
    printf("Please Enter a Character :  ");
    scanf("%c",&a);
    printf("Please Enter a Integer Value :  ");
    scanf("%d",&b);
    printf("Please Enter Float Value :  ");
    scanf("%f",&c);

    printf("The variables you entered were:\n");
    printf("The Character Value that you Entered is :  %c\n",a);
    printf("The Integer Value that you Entered is :  %d\n",b);
    printf("The Float Value that you Entered is :  %g\n",c);
    return 0;
}

