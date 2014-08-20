//version finale
void permutePointers(void **varPointer1,void **varPointer2) {
void *varTemp=*varPointer1;
    *varPointer1=*varPointer2;
    *varPointer2=varTemp;
}
