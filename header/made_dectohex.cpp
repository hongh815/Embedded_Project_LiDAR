void DecToHex(int fr1, int fr2, int fr3) {
    char massage[1024] = { 0x00 };

    sprintf(massage, "%d", fr1);
    strcat(sendm, massage);

    sprintf(massage, "%d", fr2);
    strcat(sendm, massage);

    sprintf(massage, "%d", fr3);
    strcat(sendm, massage);
}