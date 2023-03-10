#include <stdio.h>
#include <stdbool.h>

#include "menu.h"
#include "errors.h"
#include "mtr.h"
#include "mtr_struct.h"

#define OK 0

int main(void)
{
    setbuf(stdout, NULL);
    int rc = OK;

    sparse_mtr_t sparse_mtr = {.elements = NULL, .rows = NULL, .elements = NULL, .sizes.columns = 0, .sizes.rows = 0, .sizes.nonzeros = 0};
    sparse_mtr_t sparse_row = {.elements = NULL, .rows = NULL, .elements = NULL, .sizes.columns = 0, .sizes.rows = 0, .sizes.nonzeros = 0};
    mtr_t mtr = {.mtr = NULL, .sizes.rows = 0, .sizes.columns = 0, .sizes.nonzeros = 0};
    mtr_t row = {.mtr = NULL, .sizes.rows = 0, .sizes.columns = 0, .sizes.nonzeros = 0};

    print_info();
    while (true)
    {
        int action;
        print_menu();
        rc = choose_action(&action);

        if (rc)
        {
            print_error_message(rc);
            continue;
        }

        rc = do_action(action, &sparse_mtr, &sparse_row, &mtr, &row);

        if (rc)
        {
            print_error_message(rc);
            continue;
        }
    }

    return OK;
}