/*
 * Copyright (c) 2017, 2021 ADLINK Technology Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0, or the Apache License, Version 2.0
 * which is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
 *
 * Contributors:
 *   ADLINK zenoh team, <zenoh@adlink-labs.tech>
 */

#include <assert.h>
#include <stdio.h>
#include "zenoh-pico/collections/string.h"

int main(void)
{
    char s[64];
    int len = 128;

    // str-vec
    printf(">>> str-vec\n");

    _z_str_vec_t vec = _z_str_vec_make(1);
    assert(_z_str_vec_is_empty(&vec));

    for (int i = 0; i < len; i++)
    {
        sprintf(s, "%d", i);

        _z_str_vec_append(&vec, _z_str_clone(s));
        z_str_t e = _z_str_vec_get(&vec, i);
        printf("append(%d) = %s\n", i, e);
        assert(_z_str_cmp(s, e));

        _z_str_vec_set(&vec, i, _z_str_clone(s));
        e = _z_str_vec_get(&vec, i);
        printf("set(%d) = %s\n", i, e);
        assert(_z_str_cmp(s, e));

        assert(_z_str_vec_len(&vec) == i + 1);
    }
    assert(_z_str_vec_len(&vec) == len);

    _z_str_vec_clear(&vec);
    assert(_z_str_vec_is_empty(&vec));

    // str-list
    printf(">>> str-list\n");

    _z_str_list_t *list = _z_str_list_make();
    assert(_z_str_list_is_empty(list));

    for (int i = 0; i < len; i++)
    {
        sprintf(s, "%d", i);
        list = _z_str_list_push(list, _z_str_clone(s));

        z_str_t e = _z_str_list_head(list);
        printf("push(%d) = %s\n", i, e);
        assert(_z_str_cmp(s, e));

        assert(_z_str_list_len(list) == i + 1);
    }
    assert(_z_str_list_len(list) == len);

    for (int i = 0; i < len; i++)
    {
        sprintf(s, "%d", i);
        list = _z_str_list_pop(list);
        assert(_z_str_list_len(list) == len - (i + 1));
    }
    assert(_z_str_list_is_empty(list));

    for (int i = 0; i < len; i++)
    {
        sprintf(s, "%d", i);
        list = _z_str_list_push(list, _z_str_clone(s));
        assert(_z_str_cmp(s, _z_str_list_head(list)));
    }
    assert(_z_str_list_len(list) == len);
    _z_str_list_free(&list);
    assert(_z_str_list_is_empty(list));

    // str-intmap
    printf(">>> str-intmap\n");

    _z_str_intmap_t map = _z_str_intmap_make();
    assert(_z_str_intmap_is_empty(&map));

    for (int i = 0; i < len; i++)
    {
        sprintf(s, "%d", i);
        _z_str_intmap_insert(&map, i, _z_str_clone(s));

        z_str_t e = _z_str_intmap_get(&map, i);
        printf("get(%d) = %s\n", i, e);
        assert(_z_str_cmp(s, e));

        assert(_z_str_intmap_len(list) == i + 1);
    }
    assert(_z_str_intmap_len(&map) == len);

    for (int i = 0; i < len; i++)
    {
        _z_str_intmap_remove(&map, i);
        assert(_z_str_intmap_get(&map, i) == NULL);
        assert(_z_str_intmap_len(&map) == (len - 1) - i);
    }
    assert(_z_str_intmap_is_empty(&map));

    return 0;
}
