//version finale
void *getMemoryItem(const void *varMemoryItems,unsigned int intItemIndex,unsigned int intMemoryStepSize) {
    return (void *) varMemoryItems+intMemoryStepSize*intItemIndex;
}
