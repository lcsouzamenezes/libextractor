/* vim: set sw=8: -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * gsf-shared-memory.c: 
 *
 * Copyright (C) 2002-2004 Morten Welinder (terra@diku.dk)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2.1 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include "platform.h"
#include "gsf-shared-memory.h"
#include "gsf-impl-utils.h"

typedef struct {
	GObjectClass g_object_class;
} GsfSharedMemoryClass;

static GObjectClass *parent_class;

GsfSharedMemory *
gsf_shared_memory_new (void *buf, gsf_off_t size, gboolean needs_free)
{
	GsfSharedMemory *mem = g_object_new (GSF_SHARED_MEMORY_TYPE, NULL);
	if (mem == NULL)
		return NULL;
	mem->buf = buf;
	mem->size = size;
	mem->needs_free = needs_free;
	return mem;
}

static void
gsf_shared_memory_finalize (GObject *obj)
{
	GsfSharedMemory *mem = (GsfSharedMemory *) (obj);
	
	if (mem->buf != NULL) {
		if (mem->needs_free)
			g_free (mem->buf);
	}

	G_OBJECT_CLASS (parent_class)->finalize (obj);
}

static void
gsf_shared_memory_init (GObject *obj)
{
	GsfSharedMemory *mem = (GsfSharedMemory *) (obj);
	mem->buf = NULL;
}

static void
gsf_shared_memory_class_init (GObjectClass *gobject_class)
{
	parent_class = g_type_class_peek_parent (gobject_class);

	gobject_class->finalize = gsf_shared_memory_finalize;
}

GSF_CLASS (GsfSharedMemory, gsf_shared_memory,
	   gsf_shared_memory_class_init, gsf_shared_memory_init,
	   G_TYPE_OBJECT)
