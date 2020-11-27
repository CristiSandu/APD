package com.apd.tema2.entities;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Set;

/**
 * Utilizata pentru uniformizarea citirii si prelucrarii input-ului, precum si pentru eventuala initializare a unor
 * campuri.
 */
public interface ReaderHandler {
    public void handle(final String handlerType, final BufferedReader br) throws IOException;
}
