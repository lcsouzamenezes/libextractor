/* vim: set sw=8: -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * gsf-impl-utils.h:
 *
 * Copyright (C) 2002-2004 Jody Goldberg (jody@gnome.org)
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

#ifndef GSF_IMPL_UTILS_H
#define GSF_IMPL_UTILS_H

#include "gsf.h"
#include <glib-object.h>

G_BEGIN_DECLS

#define	GSF_CLASS_FULL(name, prefix, class_init, instance_init, parent_type, \
		       abstract, interface_decl) \
GType									\
prefix ## _get_type (void)						\
{									\
	static GType type = 0;						\
	if (type == 0) {						\
		static GTypeInfo const object_info = {			\
			sizeof (name ## Class),				\
			(GBaseInitFunc) NULL,				\
			(GBaseFinalizeFunc) NULL,			\
			(GClassInitFunc) class_init,			\
			(GClassFinalizeFunc) NULL,			\
			NULL,	/* class_data */			\
			sizeof (name),					\
			0,	/* n_preallocs */			\
			(GInstanceInitFunc) instance_init,		\
			NULL						\
		};							\
		type = g_type_register_static (parent_type, #name,	\
			&object_info, (GTypeFlags) abstract);		\
		interface_decl						\
	}								\
	return type;							\
}

#define	GSF_CLASS(name, prefix, class_init, instance_init, parent) \
	GSF_CLASS_FULL(name, prefix, class_init, instance_init, parent, \
		       0, {})
#define	GSF_CLASS_ABSTRACT(name, prefix, class_init, instance_init, parent) \
	GSF_CLASS_FULL(name, prefix, class_init, instance_init, parent, \
		       G_TYPE_FLAG_ABSTRACT, {})

#define	GSF_DYNAMIC_CLASS_FULL(name, prefix, class_init, instance_init, parent_type, \
			       abstract, interface_decl, plugin, type) \
	if (type == 0) {						\
		static GTypeInfo const type_info = {			\
			sizeof (name ## Class),				\
			(GBaseInitFunc) NULL,				\
			(GBaseFinalizeFunc) NULL,			\
			(GClassInitFunc) class_init,			\
			(GClassFinalizeFunc) NULL,			\
			NULL,	/* class_data */			\
			sizeof (name),					\
			0,	/* n_preallocs */			\
			(GInstanceInitFunc) instance_init,		\
			NULL						\
		};							\
		type = g_type_module_register_type (plugin, parent_type, #name,	\
			&type_info, (GTypeFlags) abstract);		\
		interface_decl						\
	}

#define	GSF_DYNAMIC_CLASS(name, prefix, class_init, instance_init, parent, plugin, type) \
	GSF_DYNAMIC_CLASS_FULL(name, prefix, class_init, instance_init, parent, \
			       0, {}, plugin, type)
#define	GSF_DYNAMIC_CLASS_ABSTRACT(name, prefix, class_init, instance_init, parent, plugin, type) \
	GSF_DYNAMIC_CLASS_FULL(name, prefix, class_init, instance_init, parent, \
		       G_TYPE_FLAG_ABSTRACT, {}, plugin, type)

#define GSF_INTERFACE_FULL(type, init_func, iface_type) {	\
	static GInterfaceInfo const iface = {			\
		(GInterfaceInitFunc) init_func, NULL, NULL };	\
	g_type_add_interface_static (type, iface_type, &iface);	\
}
#define GSF_INTERFACE(init_func, iface_type)			\
	GSF_INTERFACE_FULL(type, init_func, iface_type)

G_END_DECLS

#endif /* GSF_IMPL_UTILS_H */
