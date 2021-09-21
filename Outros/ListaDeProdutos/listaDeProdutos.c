 #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

        struct loja{
            int code;
            char name[50];
            int quantity;
            float price;

        }*product;

    void most_expansive( struct loja product[], int quantity_of);
    void highest_quantity(struct loja product[], int quantity_of);

    int main()
    {

        int quantity_of;

        printf("\n\nType the quantoty of the poducts: ");
        scanf("%d", &quantity_of);

        product = (struct loja*) malloc (quantity_of * sizeof(struct loja));

        printf("///////////////Fill the list od products////////////////");

        for( int i =0; i < quantity_of; i++)
        {
            printf("\n\nCode: ");
            scanf("%d", &product[i].code);
            printf("\n\nName: ");
            fflush(stdin);
            gets(product[i].name);
            printf("\n\nQuantity: ");
            scanf("%d", &product[i].quantity);
            printf("\n\nPrice: R$ ");
            scanf("%f", &product[i].price);
        }

        most_expansive(product, quantity_of);

        highest_quantity(product, quantity_of);

        return 0;
    }

    void most_expansive(struct loja product[], int quantity_of)
    {
        char *mostExpansive;
        float mostExpansiveprice = 1;

        mostExpansive = (char *) malloc ( 50 * sizeof(char));
        for (int i = 0; i < quantity_of; i++ )
        {
            if ( product[i].price >= mostExpansiveprice)
            {
                mostExpansiveprice = product[i].price;

                mostExpansive = (char*) realloc (mostExpansive, sizeof(product[i].name));
                strcpy(mostExpansive, product[i].name);   
            }
        }

        printf("\n\n> The most expansive product is %s that costs R$ %.2f", mostExpansive, mostExpansiveprice);
    }

    void highest_quantity(struct loja product[], int quantity_of)
    {
        int highestQuantity = 1;
        char *highestQuantityname;

        highestQuantityname = (char *) malloc ( 50 * sizeof(char));

       for (int i = 0; i < quantity_of; i++ )
        {
            if ( product[i].quantity >= highestQuantity)
            {
                highestQuantity = product[i].quantity;

                highestQuantityname = (char*) realloc (highestQuantityname, sizeof(product[i].name));
                strcpy(highestQuantityname, product[i].name);   
            }
        }
        printf("\n\n> The product that is in highest quantity is %s that have %d units", highestQuantityname, highestQuantity);

    }