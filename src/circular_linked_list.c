/*
Copyright (c) 2016, Neeraj Prasad
 All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- Neither the name of the 'incremental' nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE. */


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
 
#include "../include/circular_linked_list.h"

void insert_memory_node(x_memory_node *head_mem_node, uint32_t node_size, uint32_t flag)
{
    x_memory_node *tmp_node = NULL;
    x_memory_node *p= NULL;
    tmp_node = (x_memory_node *)malloc(sizeof(x_memory_node));
    tmp_node->data_buffer = (uint8_t *)malloc(node_size);
    tmp_node->frame_count = flag;
    p=head_mem_node;
    while(p->next_mem != head_mem_node)
        p=p->next_mem;
    p->next_mem = tmp_node;
    tmp_node->next_mem = head_mem_node;
    return;
}

x_memory_node *prepare_memory_node(uint32_t count, uint32_t node_size)
{
    int32_t counter = 0;
    x_memory_node *head_mem_node = NULL;

    head_mem_node = (x_memory_node *)malloc(sizeof(x_memory_node));
    head_mem_node->data_buffer = (uint8_t *)malloc(node_size);
    head_mem_node->frame_count = 1;
    head_mem_node->buffer_size = 0;

    x_memory_node *mem_node = NULL;
    mem_node = (x_memory_node *)malloc(sizeof(x_memory_node));
    mem_node->data_buffer = (uint8_t *)malloc(node_size);
    mem_node->frame_count = 2;
    mem_node->buffer_size = 0;
    mem_node->next_mem = head_mem_node;
    head_mem_node->next_mem = mem_node;

    while(counter++ < (count -2))
        insert_memory_node(head_mem_node, node_size, counter+2);
    return head_mem_node;
}

void delete_full_node(x_memory_node *head_node)
{
    x_memory_node *tmp_node = head_node;
    while (head_node != NULL)
    {
        tmp_node = head_node;
        if (tmp_node->next_mem == head_node)
        {
            tmp_node = head_node;
            head_node = NULL;
        }
        else
        {
            tmp_node = head_node->next_mem;
            head_node->next_mem = tmp_node->next_mem;
        }
        free(tmp_node->data_buffer);
        tmp_node->data_buffer = NULL;
        free(tmp_node);
        tmp_node = NULL;
    }
    
    return;
}

x_memory_node *get_next_node(x_memory_node *current_node)
{
    if (current_node != NULL)
    {
       return current_node->next_mem;
    }
    return NULL;
}



