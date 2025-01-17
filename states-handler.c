void registerState();
int stateValidation(char currentState[]);
int stateLengthValidation(char currentState[]);
void storeState(char currentState[]);

//It's the main procedure of the register state option, organizing and calling other functions and printing validations
void registerState() {
    printf("Informe a sigla da Unidade Federativa a ser cadastrada:\n");

    char receivedState[3];
	fgets(receivedState, 5, stdin);
	fflush(stdin);

    trim(receivedState, NULL);
    convertToLowercase(receivedState);

    if (stateLengthValidation(receivedState) == 1) {
        if (stateValidation(receivedState) == 1) {
            storeState(receivedState);
        } else {
            printf("\nO Estado informado nao existe, informe uma sigla valida.\n");
        }
    } else {
        printf("\nSigla de Estado invalida, informe uma sigla valida.\n");
    }

    printf("\nAperte ENTER para voltar ao menu.\n");
    fgetc(stdin);
}

//Opens a already prepared archive which contains the 27 states acronyms to compare and validate
int stateValidation(char currentState[]) {
    char readState[3];
    FILE *validationFile;

    validationFile = fopen("statesValidation.txt", "r");
    if (validationFile == NULL) {
        printf("\nArquivo de valida��o de Estados n�o existe.\n");
        exit(1);
    }

    while(fgets(readState, sizeof(readState), validationFile) != NULL) {
        if (strcmp(readState, currentState) == 0) {
            fclose(validationFile);
            return 1;
        } else {
            //Nada a fazer.
        }
    }
    return 0;
    fclose(validationFile);
}

//Validate the length of the state array
int stateLengthValidation(char currentState[]) {
	int receivedStateLength = strlen(currentState);

	if (receivedStateLength == 2){
        return 1;
	} else {
        return 0;
	}
}

//Opens an archive and store the given state acronym if it isn't already registered
void storeState(char currentState[]) {
    char readState[3];
    int alreadyRegistered = 0;

    FILE *statesFile;
    statesFile = fopen("states.txt", "a+");

    while(fgets(readState, sizeof(readState), statesFile) != NULL) {
        if (strcmp(readState, currentState) == 0) {
            alreadyRegistered = 1;
        } else {
            //Nada a fazer.
        }
    }

    if (alreadyRegistered) {
        printf("\nEste Estado ja esta cadastrado.\n");
    } else {
        fprintf(statesFile, "%s\n", currentState);
        printf("\nEstado cadastrado com sucesso!\n");
    }

    fclose(statesFile);
}
