/****************************************************************************
 * File:	modnuklear.c
 * Brief:		

integration steps:
1.
file: mpconfigport.h
line: // extra built in modules to add to the list
add : extern const struct _mp_obj_module_t nuklear_module;
2.
file: mpconfigport.h
line: // #define MICROPY_PORT_BUILTIN_MODULES
add : { MP_ROM_QSTR(MP_QSTR_nuklear), (mp_obj_t)&nuklear_module }, 
3.
file: makefile.mk
line: // SRC_C =  
add : modnuklear.c 

 * Author:		
 ****************************************************************************/
/****************************************************************************
 * Private Includes.
 ****************************************************************************/
#include	<stdio.h>
#include	<string.h>

#include	"modnuklear.h"
#include	"py/obj.h"
#include "py/objarray.h"
#include	"py/runtime.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"

/****************************************************************************
 * Private Defines.
 ****************************************************************************/
//#define	MODULE_NUKLEAR_ENABLED	(1)
MP_REGISTER_MODULE(MP_QSTR_nuklear, nuklear_module );

/****************************************************************************
 * Private Types.
 ****************************************************************************/
typedef struct sNk tNk;
struct sNk
{
    mp_obj_base_t base;
    struct nk_context ctx;
    struct nk_buffer cmds;
    struct nk_buffer pool;
    struct nk_user_font font;
};

/****************************************************************************
 * Private Functions Declarations.
 ****************************************************************************/
STATIC mp_obj_t Nk_make_new( const mp_obj_type_t *type_in, size_t n_args, size_t n_kw, const mp_obj_t *args_in );
STATIC void Nk_print( const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind );

STATIC mp_obj_t Nk_draw(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_set_style(size_t n_args, const mp_obj_t *args_in);

STATIC mp_obj_t Nk_clear(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_input_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_input_motion(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_input_button(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_input_char(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_input_key(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_input_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_button_color(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_button_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_button_set_behavior(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_button_symbol(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_button_symbol_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_add_slot(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_add_slot_colored(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_begin_colored(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_push(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_chart_push_slot(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_checkbox_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_color_pick(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_color_picker(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_combo(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_combo_begin_color(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_combo_begin_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_combo_close(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_combo_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_contextual_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_contextual_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_contextual_item_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_edit_string(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_group_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_group_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_label_colored(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_label_wrap(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_dynamic(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_push(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_static(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_template_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_template_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_template_push_dynamic(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_template_push_static(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_row_template_push_variable(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_space_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_space_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_layout_space_push(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_menu_begin_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_menu_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_menu_item_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_menubar_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_menubar_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_option_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_plot(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_popup_begin(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_popup_close(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_popup_end(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_prog(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_progress(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_property_float(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_property_int(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_propertyf(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_propertyi(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_selectable_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_selectable_symbol_label(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_slide_int(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_slider_float(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_slider_int(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_spacing(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_text(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_tooltip(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_tree_element_pop(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_tree_state_push(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_widget(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_widget_bounds(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_window_is_closed(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_tree_push(size_t n_args, const mp_obj_t *args_in);
STATIC mp_obj_t Nk_tree_pop(size_t n_args, const mp_obj_t *args_in);

/****************************************************************************
 * Private Variables Declarations.
 ****************************************************************************/
STATIC const mp_obj_fun_builtin_var_t Nk_draw_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_set_style_obj;

STATIC const mp_obj_fun_builtin_var_t Nk_clear_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_input_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_input_motion_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_input_button_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_input_char_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_input_key_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_input_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_button_color_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_button_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_button_set_behavior_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_button_symbol_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_button_symbol_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_add_slot_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_add_slot_colored_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_begin_colored_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_push_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_chart_push_slot_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_checkbox_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_color_pick_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_color_picker_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_combo_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_combo_begin_color_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_combo_begin_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_combo_close_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_combo_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_contextual_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_contextual_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_contextual_item_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_edit_string_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_group_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_group_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_label_colored_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_label_wrap_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_dynamic_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_push_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_static_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_template_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_template_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_template_push_dynamic_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_template_push_static_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_row_template_push_variable_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_space_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_space_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_layout_space_push_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_menu_begin_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_menu_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_menu_item_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_menubar_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_menubar_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_option_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_plot_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_popup_begin_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_popup_close_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_popup_end_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_prog_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_progress_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_property_float_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_property_int_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_propertyf_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_propertyi_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_selectable_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_selectable_symbol_label_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_slide_int_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_slider_float_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_slider_int_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_spacing_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_text_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_tooltip_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_tree_element_pop_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_tree_state_push_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_widget_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_widget_bounds_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_window_is_closed_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_tree_push_obj;
STATIC const mp_obj_fun_builtin_var_t Nk_tree_pop_obj;

const mp_rom_map_elem_t Nk_locals_dict_table[];
STATIC const mp_obj_dict_t Nk_locals_dict;
const mp_obj_type_t Nk_type;
const mp_map_elem_t nuklear_globals_table[];
STATIC const mp_obj_dict_t nuklear_globals;
const mp_obj_module_t nuklear_module;

/****************************************************************************
 * Private Variables Definitions.
 ****************************************************************************/
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_draw_obj, 4, 4, Nk_draw );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_set_style_obj, 2, 2, Nk_set_style );

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_clear_obj, 1, 1, Nk_clear );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_input_begin_obj, 1, 1, Nk_input_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_input_motion_obj, 3, 3, Nk_input_motion );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_input_button_obj, 5, 5, Nk_input_button );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_input_char_obj, 2, 2, Nk_input_char );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_input_key_obj, 3, 3, Nk_input_key );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_input_end_obj, 1, 1, Nk_input_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_begin_obj, 4, 4, Nk_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_button_color_obj, 2, 2, Nk_button_color );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_button_label_obj, 2, 2, Nk_button_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_button_set_behavior_obj, 2, 2, Nk_button_set_behavior );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_button_symbol_obj, 2, 2, Nk_button_symbol );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_button_symbol_label_obj, 4, 4, Nk_button_symbol_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_add_slot_obj, 5, 5, Nk_chart_add_slot );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_add_slot_colored_obj, 7, 7, Nk_chart_add_slot_colored );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_begin_obj, 5, 5, Nk_chart_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_begin_colored_obj, 7, 7, Nk_chart_begin_colored );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_end_obj, 1, 1, Nk_chart_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_push_obj, 2, 2, Nk_chart_push );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_chart_push_slot_obj, 3, 3, Nk_chart_push_slot );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_checkbox_label_obj, 3, 3, Nk_checkbox_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_color_pick_obj, 3, 3, Nk_color_pick );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_color_picker_obj, 3, 3, Nk_color_picker );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_combo_obj, 6, 6, Nk_combo );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_combo_begin_color_obj, 3, 3, Nk_combo_begin_color );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_combo_begin_label_obj, 3, 3, Nk_combo_begin_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_combo_close_obj, 1, 1, Nk_combo_close );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_combo_end_obj, 1, 1, Nk_combo_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_contextual_begin_obj, 4, 4, Nk_contextual_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_contextual_end_obj, 1, 1, Nk_contextual_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_contextual_item_label_obj, 3, 3, Nk_contextual_item_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_edit_string_obj, 6, 6, Nk_edit_string );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_end_obj, 1, 1, Nk_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_group_begin_obj, 3, 3, Nk_group_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_group_end_obj, 1, 1, Nk_group_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_label_obj, 3, 3, Nk_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_label_colored_obj, 4, 4, Nk_label_colored );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_label_wrap_obj, 2, 2, Nk_label_wrap );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_obj, 5, 5, Nk_layout_row );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_begin_obj, 4, 4, Nk_layout_row_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_dynamic_obj, 3, 3, Nk_layout_row_dynamic );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_end_obj, 1, 1, Nk_layout_row_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_push_obj, 2, 2, Nk_layout_row_push );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_static_obj, 4, 4, Nk_layout_row_static );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_template_begin_obj, 2, 2, Nk_layout_row_template_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_template_end_obj, 1, 1, Nk_layout_row_template_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_template_push_dynamic_obj, 1, 1, Nk_layout_row_template_push_dynamic );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_template_push_static_obj, 2, 2, Nk_layout_row_template_push_static );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_row_template_push_variable_obj, 2, 2, Nk_layout_row_template_push_variable );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_space_begin_obj, 4, 4, Nk_layout_space_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_space_end_obj, 1, 1, Nk_layout_space_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_layout_space_push_obj, 2, 2, Nk_layout_space_push );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_menu_begin_label_obj, 4, 4, Nk_menu_begin_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_menu_end_obj, 1, 1, Nk_menu_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_menu_item_label_obj, 3, 3, Nk_menu_item_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_menubar_begin_obj, 1, 1, Nk_menubar_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_menubar_end_obj, 1, 1, Nk_menubar_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_option_label_obj, 3, 3, Nk_option_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_plot_obj, 5, 5, Nk_plot );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_popup_begin_obj, 5, 5, Nk_popup_begin );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_popup_close_obj, 1, 1, Nk_popup_close );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_popup_end_obj, 1, 1, Nk_popup_end );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_prog_obj, 4, 4, Nk_prog );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_progress_obj, 4, 4, Nk_progress );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_property_float_obj, 7, 7, Nk_property_float );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_property_int_obj, 7, 7, Nk_property_int );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_propertyf_obj, 7, 7, Nk_propertyf );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_propertyi_obj, 7, 7, Nk_propertyi );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_selectable_label_obj, 4, 4, Nk_selectable_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_selectable_symbol_label_obj, 5, 5, Nk_selectable_symbol_label );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_slide_int_obj, 5, 5, Nk_slide_int );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_slider_float_obj, 5, 5, Nk_slider_float );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_slider_int_obj, 5, 5, Nk_slider_int );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_spacing_obj, 2, 2, Nk_spacing );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_text_obj, 4, 4, Nk_text );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_tooltip_obj, 2, 2, Nk_tooltip );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_tree_element_pop_obj, 1, 1, Nk_tree_element_pop );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_tree_state_push_obj, 4, 4, Nk_tree_state_push );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_widget_obj, 2, 2, Nk_widget );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_widget_bounds_obj, 1, 1, Nk_widget_bounds );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_window_is_closed_obj, 2, 2, Nk_window_is_closed );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_tree_push_obj, 4, 4, Nk_tree_push );
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Nk_tree_pop_obj, 1, 1, Nk_tree_pop );

const mp_rom_map_elem_t Nk_locals_dict_table[] = 
{
    { MP_ROM_QSTR( MP_QSTR_draw ), MP_ROM_PTR( &Nk_draw_obj) },
    { MP_ROM_QSTR( MP_QSTR_set_style ), MP_ROM_PTR( &Nk_set_style_obj) },
    
    { MP_ROM_QSTR( MP_QSTR_clear ), MP_ROM_PTR( &Nk_clear_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_begin ), MP_ROM_PTR( &Nk_input_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_motion ), MP_ROM_PTR( &Nk_input_motion_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_button ), MP_ROM_PTR( &Nk_input_button_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_char ), MP_ROM_PTR( &Nk_input_char_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_key ), MP_ROM_PTR( &Nk_input_key_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_end ), MP_ROM_PTR( &Nk_input_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin ), MP_ROM_PTR( &Nk_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_button_color ), MP_ROM_PTR( &Nk_button_color_obj) },
    { MP_ROM_QSTR( MP_QSTR_button_label ), MP_ROM_PTR( &Nk_button_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_button_set_behavior ), MP_ROM_PTR( &Nk_button_set_behavior_obj) },
    { MP_ROM_QSTR( MP_QSTR_button_symbol ), MP_ROM_PTR( &Nk_button_symbol_obj) },
    { MP_ROM_QSTR( MP_QSTR_button_symbol_label ), MP_ROM_PTR( &Nk_button_symbol_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_add_slot ), MP_ROM_PTR( &Nk_chart_add_slot_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_add_slot_colored ), MP_ROM_PTR( &Nk_chart_add_slot_colored_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_begin ), MP_ROM_PTR( &Nk_chart_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_begin_colored ), MP_ROM_PTR( &Nk_chart_begin_colored_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_end ), MP_ROM_PTR( &Nk_chart_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_push ), MP_ROM_PTR( &Nk_chart_push_obj) },
    { MP_ROM_QSTR( MP_QSTR_chart_push_slot ), MP_ROM_PTR( &Nk_chart_push_slot_obj) },
    { MP_ROM_QSTR( MP_QSTR_checkbox_label ), MP_ROM_PTR( &Nk_checkbox_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_color_pick ), MP_ROM_PTR( &Nk_color_pick_obj) },
    { MP_ROM_QSTR( MP_QSTR_color_picker ), MP_ROM_PTR( &Nk_color_picker_obj) },
    { MP_ROM_QSTR( MP_QSTR_combo ), MP_ROM_PTR( &Nk_combo_obj) },
    { MP_ROM_QSTR( MP_QSTR_combo_begin_color ), MP_ROM_PTR( &Nk_combo_begin_color_obj) },
    { MP_ROM_QSTR( MP_QSTR_combo_begin_label ), MP_ROM_PTR( &Nk_combo_begin_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_combo_close ), MP_ROM_PTR( &Nk_combo_close_obj) },
    { MP_ROM_QSTR( MP_QSTR_combo_end ), MP_ROM_PTR( &Nk_combo_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_contextual_begin ), MP_ROM_PTR( &Nk_contextual_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_contextual_end ), MP_ROM_PTR( &Nk_contextual_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_contextual_item_label ), MP_ROM_PTR( &Nk_contextual_item_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_edit_string ), MP_ROM_PTR( &Nk_edit_string_obj) },
    { MP_ROM_QSTR( MP_QSTR_end ), MP_ROM_PTR( &Nk_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_group_begin ), MP_ROM_PTR( &Nk_group_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_group_end ), MP_ROM_PTR( &Nk_group_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_label ), MP_ROM_PTR( &Nk_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_label_colored ), MP_ROM_PTR( &Nk_label_colored_obj) },
    { MP_ROM_QSTR( MP_QSTR_label_wrap ), MP_ROM_PTR( &Nk_label_wrap_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row ), MP_ROM_PTR( &Nk_layout_row_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_begin ), MP_ROM_PTR( &Nk_layout_row_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_dynamic ), MP_ROM_PTR( &Nk_layout_row_dynamic_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_end ), MP_ROM_PTR( &Nk_layout_row_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_push ), MP_ROM_PTR( &Nk_layout_row_push_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_static ), MP_ROM_PTR( &Nk_layout_row_static_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_template_begin ), MP_ROM_PTR( &Nk_layout_row_template_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_template_end ), MP_ROM_PTR( &Nk_layout_row_template_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_template_push_dynamic ), MP_ROM_PTR( &Nk_layout_row_template_push_dynamic_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_template_push_static ), MP_ROM_PTR( &Nk_layout_row_template_push_static_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row_template_push_variable ), MP_ROM_PTR( &Nk_layout_row_template_push_variable_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_space_begin ), MP_ROM_PTR( &Nk_layout_space_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_space_end ), MP_ROM_PTR( &Nk_layout_space_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_space_push ), MP_ROM_PTR( &Nk_layout_space_push_obj) },
    { MP_ROM_QSTR( MP_QSTR_menu_begin_label ), MP_ROM_PTR( &Nk_menu_begin_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_menu_end ), MP_ROM_PTR( &Nk_menu_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_menu_item_label ), MP_ROM_PTR( &Nk_menu_item_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_menubar_begin ), MP_ROM_PTR( &Nk_menubar_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_menubar_end ), MP_ROM_PTR( &Nk_menubar_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_option_label ), MP_ROM_PTR( &Nk_option_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_plot ), MP_ROM_PTR( &Nk_plot_obj) },
    { MP_ROM_QSTR( MP_QSTR_popup_begin ), MP_ROM_PTR( &Nk_popup_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_popup_close ), MP_ROM_PTR( &Nk_popup_close_obj) },
    { MP_ROM_QSTR( MP_QSTR_popup_end ), MP_ROM_PTR( &Nk_popup_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_prog ), MP_ROM_PTR( &Nk_prog_obj) },
    { MP_ROM_QSTR( MP_QSTR_progress ), MP_ROM_PTR( &Nk_progress_obj) },
    { MP_ROM_QSTR( MP_QSTR_property_float ), MP_ROM_PTR( &Nk_property_float_obj) },
    { MP_ROM_QSTR( MP_QSTR_property_int ), MP_ROM_PTR( &Nk_property_int_obj) },
    { MP_ROM_QSTR( MP_QSTR_propertyf ), MP_ROM_PTR( &Nk_propertyf_obj) },
    { MP_ROM_QSTR( MP_QSTR_propertyi ), MP_ROM_PTR( &Nk_propertyi_obj) },
    { MP_ROM_QSTR( MP_QSTR_selectable_label ), MP_ROM_PTR( &Nk_selectable_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_selectable_symbol_label ), MP_ROM_PTR( &Nk_selectable_symbol_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_slide_int ), MP_ROM_PTR( &Nk_slide_int_obj) },
    { MP_ROM_QSTR( MP_QSTR_slider_float ), MP_ROM_PTR( &Nk_slider_float_obj) },
    { MP_ROM_QSTR( MP_QSTR_slider_int ), MP_ROM_PTR( &Nk_slider_int_obj) },
    { MP_ROM_QSTR( MP_QSTR_spacing ), MP_ROM_PTR( &Nk_spacing_obj) },
    { MP_ROM_QSTR( MP_QSTR_text ), MP_ROM_PTR( &Nk_text_obj) },
    { MP_ROM_QSTR( MP_QSTR_tooltip ), MP_ROM_PTR( &Nk_tooltip_obj) },
    { MP_ROM_QSTR( MP_QSTR_tree_element_pop ), MP_ROM_PTR( &Nk_tree_element_pop_obj) },
    { MP_ROM_QSTR( MP_QSTR_tree_state_push ), MP_ROM_PTR( &Nk_tree_state_push_obj) },
    { MP_ROM_QSTR( MP_QSTR_widget ), MP_ROM_PTR( &Nk_widget_obj) },
    { MP_ROM_QSTR( MP_QSTR_widget_bounds ), MP_ROM_PTR( &Nk_widget_bounds_obj) },
    { MP_ROM_QSTR( MP_QSTR_window_is_closed ), MP_ROM_PTR( &Nk_window_is_closed_obj) },
    { MP_ROM_QSTR( MP_QSTR_tree_push ), MP_ROM_PTR( &Nk_tree_push_obj) },
    { MP_ROM_QSTR( MP_QSTR_tree_pop ), MP_ROM_PTR( &Nk_tree_pop_obj) },
    
    { MP_ROM_QSTR(MP_QSTR_WINDOW_BORDER), MP_ROM_INT(NK_WINDOW_BORDER) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_MOVABLE), MP_ROM_INT(NK_WINDOW_MOVABLE) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_SCALABLE), MP_ROM_INT(NK_WINDOW_SCALABLE) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_CLOSABLE), MP_ROM_INT(NK_WINDOW_CLOSABLE) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_MINIMIZABLE), MP_ROM_INT(NK_WINDOW_MINIMIZABLE) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_NO_SCROLLBAR), MP_ROM_INT(NK_WINDOW_NO_SCROLLBAR) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_TITLE), MP_ROM_INT(NK_WINDOW_TITLE) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_SCROLL_AUTO_HIDE), MP_ROM_INT(NK_WINDOW_SCROLL_AUTO_HIDE) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_BACKGROUND), MP_ROM_INT(NK_WINDOW_BACKGROUND) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_SCALE_LEFT), MP_ROM_INT(NK_WINDOW_SCALE_LEFT) },
    { MP_ROM_QSTR(MP_QSTR_WINDOW_NO_INPUT), MP_ROM_INT(NK_WINDOW_NO_INPUT) },

    { MP_ROM_QSTR(MP_QSTR_TEXT_ALIGN_LEFT), MP_ROM_INT(NK_TEXT_ALIGN_LEFT) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_ALIGN_CENTERED), MP_ROM_INT(NK_TEXT_ALIGN_CENTERED) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_ALIGN_RIGHT), MP_ROM_INT(NK_TEXT_ALIGN_RIGHT) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_ALIGN_TOP), MP_ROM_INT(NK_TEXT_ALIGN_TOP) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_ALIGN_MIDDLE), MP_ROM_INT(NK_TEXT_ALIGN_MIDDLE) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_ALIGN_BOTTOM), MP_ROM_INT(NK_TEXT_ALIGN_BOTTOM) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_LEFT), MP_ROM_INT(NK_TEXT_LEFT) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_CENTERED), MP_ROM_INT(NK_TEXT_CENTERED) },
    { MP_ROM_QSTR(MP_QSTR_TEXT_RIGHT), MP_ROM_INT(NK_TEXT_RIGHT) },
    
    { MP_ROM_QSTR(MP_QSTR_UP), MP_ROM_INT(NK_UP) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_INT(NK_RIGHT) },
    { MP_ROM_QSTR(MP_QSTR_DOWN), MP_ROM_INT(NK_DOWN) },
    { MP_ROM_QSTR(MP_QSTR_LEFT), MP_ROM_INT(NK_LEFT) },
    { MP_ROM_QSTR(MP_QSTR_BUTTON_DEFAULT), MP_ROM_INT(NK_BUTTON_DEFAULT) },
    { MP_ROM_QSTR(MP_QSTR_BUTTON_REPEATER), MP_ROM_INT(NK_BUTTON_REPEATER) },
    { MP_ROM_QSTR(MP_QSTR_FIXED), MP_ROM_INT(NK_FIXED) },
    { MP_ROM_QSTR(MP_QSTR_MODIFIABLE), MP_ROM_INT(NK_MODIFIABLE) },
    { MP_ROM_QSTR(MP_QSTR_VERTICAL), MP_ROM_INT(NK_VERTICAL) },
    { MP_ROM_QSTR(MP_QSTR_HORIZONTAL), MP_ROM_INT(NK_HORIZONTAL) },
    { MP_ROM_QSTR(MP_QSTR_MINIMIZED), MP_ROM_INT(NK_MINIMIZED) },
    { MP_ROM_QSTR(MP_QSTR_MAXIMIZED), MP_ROM_INT(NK_MAXIMIZED) },
    { MP_ROM_QSTR(MP_QSTR_HIDDEN), MP_ROM_INT(NK_HIDDEN) },
    { MP_ROM_QSTR(MP_QSTR_SHOWN), MP_ROM_INT(NK_SHOWN) },
    { MP_ROM_QSTR(MP_QSTR_CHART_LINES), MP_ROM_INT(NK_CHART_LINES) },
    { MP_ROM_QSTR(MP_QSTR_CHART_COLUMN), MP_ROM_INT(NK_CHART_COLUMN) },
    { MP_ROM_QSTR(MP_QSTR_CHART_MAX), MP_ROM_INT(NK_CHART_MAX) },
    { MP_ROM_QSTR(MP_QSTR_CHART_HOVERING), MP_ROM_INT(NK_CHART_HOVERING) },
    { MP_ROM_QSTR(MP_QSTR_CHART_CLICKED), MP_ROM_INT(NK_CHART_CLICKED) },
    { MP_ROM_QSTR(MP_QSTR_RGB), MP_ROM_INT(NK_RGB) },
    { MP_ROM_QSTR(MP_QSTR_RGBA), MP_ROM_INT(NK_RGBA) },
    { MP_ROM_QSTR(MP_QSTR_POPUP_STATIC), MP_ROM_INT(NK_POPUP_STATIC) },
    { MP_ROM_QSTR(MP_QSTR_POPUP_DYNAMIC), MP_ROM_INT(NK_POPUP_DYNAMIC) },
    { MP_ROM_QSTR(MP_QSTR_DYNAMIC), MP_ROM_INT(NK_DYNAMIC) },
    { MP_ROM_QSTR(MP_QSTR_STATIC), MP_ROM_INT(NK_STATIC) },
    { MP_ROM_QSTR(MP_QSTR_TREE_NODE), MP_ROM_INT(NK_TREE_NODE) },
    { MP_ROM_QSTR(MP_QSTR_TREE_TAB), MP_ROM_INT(NK_TREE_TAB) },
    
};
const mp_obj_type_t Nk_type = 
{
    { &mp_type_type },
    .name = MP_QSTR_Nk,
    .make_new = Nk_make_new,
    .print = Nk_print,
    .locals_dict = (mp_obj_dict_t*)&Nk_locals_dict,
};
const mp_map_elem_t nuklear_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR( MP_QSTR___name__ ), MP_OBJ_NEW_QSTR( MP_QSTR_nuklear ) },
    { MP_OBJ_NEW_QSTR( MP_QSTR_Nk ), (mp_obj_t)&Nk_type },
};
const mp_obj_module_t nuklear_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&nuklear_globals,
};

/****************************************************************************
 * Public Variables Definitions.
 ****************************************************************************/
STATIC MP_DEFINE_CONST_DICT( Nk_locals_dict, Nk_locals_dict_table );
STATIC MP_DEFINE_CONST_DICT( nuklear_globals, nuklear_globals_table );

/****************************************************************************
 * Private Functions Definitions.
 ****************************************************************************/
float text_width_f( nk_handle handle, float h, const char* t, int len )
{
    return 8*len;
}

STATIC mp_obj_t Nk_make_new( const mp_obj_type_t *type_in, size_t n_args, size_t n_kw, const mp_obj_t *args_in )
{
    mp_arg_check_num( n_args, n_kw, 2, 2, false );
    tNk *self = m_new_obj( tNk );
    self->base.type = &Nk_type;
    self->ctx = (struct nk_context){0};
    self->cmds = (struct nk_buffer){0};
    self->pool = (struct nk_buffer){0};
    self->font = (struct nk_user_font){0};
    
    self->font.height = 8;
    self->font.width = text_width_f;
    
    mp_buffer_info_t bufinfo_cmds;
    mp_get_buffer_raise(args_in[0], &bufinfo_cmds, MP_BUFFER_WRITE);
    mp_buffer_info_t bufinfo_pool;
    mp_get_buffer_raise(args_in[1], &bufinfo_pool, MP_BUFFER_WRITE);
    
    nk_buffer_init_fixed(&self->cmds, bufinfo_cmds.buf, bufinfo_cmds.len);
    nk_buffer_init_fixed(&self->pool, bufinfo_pool.buf, bufinfo_pool.len);
    
    nk_init_custom( &self->ctx, &self->cmds, &self->pool, &self->font );
    
    return MP_OBJ_FROM_PTR( self );
}

STATIC void Nk_print( const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind )
{
    (void)kind;
    tNk *self = MP_OBJ_TO_PTR( self_in );
    mp_printf( print, "Nk=%x\n", (int)self );
}


uint16_t rgb_to_565( uint8_t r, uint8_t g, uint8_t b )
{
    uint16_t color = ( (r & 0xf8) << 8 ) | ( (g & 0xfc) << 3 ) | ( b >> 3 );
    color = ( (color & 0xff) << 8 ) | ( (color & 0xff00) >> 8 );
    return color;
}

uint16_t rgba_to_565( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
    float fa = 1;//a / 255.0;
    r = r * fa;
    g = g * fa;
    b = b * fa;
    return rgb_to_565( r, g, b );
}

typedef struct _mp_obj_framebuf_t mp_obj_framebuf_t;
extern mp_obj_t framebuf_line(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_rect(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_fill_rect(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_text(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_ellipse(size_t n_args, const mp_obj_t *args_in);
extern mp_obj_t framebuf_poly(size_t n_args, const mp_obj_t *args_in);

STATIC mp_obj_t Nk_draw(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    //struct nk_buffer* cmds = &self->cmds;
    // framebuffer = args_in[1];
    int x0 = -mp_obj_get_int( args_in[1] );
    int y0 = -mp_obj_get_int( args_in[2] );
    mp_obj_framebuf_t *fb_in = MP_OBJ_TO_PTR( args_in[3] );
    
    const struct nk_command *cmd = NULL;
    nk_foreach(cmd, ctx)
    {
        switch (cmd->type) {
        case NK_COMMAND_NOP: break;
        case NK_COMMAND_SCISSOR: {
            const struct nk_command_scissor *s = (const struct nk_command_scissor*)cmd;
            //nk_draw_list_add_clip(&ctx->draw_list, nk_rect(s->x, s->y, s->w, s->h));
            //printf("scissor %d %d %d %d\n", s->x, s->y, s->w, s->h);
        } break;
        case NK_COMMAND_LINE: {
            const struct nk_command_line *l = (const struct nk_command_line*)cmd;
            //nk_draw_list_stroke_line(&ctx->draw_list, nk_vec2(l->begin.x, l->begin.y),
            //    nk_vec2(l->end.x, l->end.y), l->color, l->line_thickness);
            //printf("line %d %d %d %d\n", l->begin.x, l->begin.y, l->end.x, l->end.y);
            framebuf_line(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+l->begin.x),
                    mp_obj_new_int(y0+l->begin.y),
                    mp_obj_new_int(x0+l->end.x),
                    mp_obj_new_int(y0+l->end.y),
                    mp_obj_new_int(rgba_to_565(l->color.r, l->color.g, l->color.b, l->color.a))
                }
            );
        } break;
        /*case NK_COMMAND_RECT: {
            const struct nk_command_rect *r = (const struct nk_command_rect*)cmd;
            //nk_draw_list_stroke_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
            //    r->color, (float)r->rounding, r->line_thickness);
            //printf("rect %d %d %d %d\n", r->x, r->y, r->w, r->h);
            framebuf_rect(6,
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x),
                    mp_obj_new_int(y0+r->y),
                    mp_obj_new_int(r->w),
                    mp_obj_new_int(r->h),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
        } break;*/
        case NK_COMMAND_RECT: {
            const struct nk_command_rect *r = (const struct nk_command_rect*)cmd;
            //nk_draw_list_stroke_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
            //    r->color, (float)r->rounding, r->line_thickness);
            //printf("rect %d %d %d %d\n", r->x, r->y, r->w, r->h);
            
            // draw 4 lines then four corners.
            framebuf_line(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int(x0+r->x),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            framebuf_line(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y),
                    mp_obj_new_int(x0+r->x+r->w-(int)r->rounding),
                    mp_obj_new_int(y0+r->y),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            framebuf_line(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+r->w),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int(x0+r->x+r->w),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            framebuf_line(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h),
                    mp_obj_new_int(x0+r->x+r->w-(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            //int rrr = (float)r->rounding;
            //printf( "%f %d\n", (float)r->rounding, rrr );
            if( r->rounding < 0.1f )
            {
                break;
            }
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(0),
                    mp_obj_new_int(0x02) // top left
                }
            );
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+r->w-(int)r->rounding),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(0),
                    mp_obj_new_int(0x01) // top right
                }
            );
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(0),
                    mp_obj_new_int(0x04) // bottom left
                }
            );
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+r->w-(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(0),
                    mp_obj_new_int(0x08) // bottom right
                }
            );
        } break;
        case NK_COMMAND_RECT_FILLED: {
            const struct nk_command_rect_filled *r = (const struct nk_command_rect_filled*)cmd;
            //nk_draw_list_fill_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
            //    r->color, (float)r->rounding);
            //printf("rect filled %d %d %d %d\n", r->x, r->y, r->w, r->h);
            /*framebuf_fill_rect(6,
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x),
                    mp_obj_new_int(y0+r->y),
                    mp_obj_new_int(r->w),
                    mp_obj_new_int(r->h),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );*/
            // draw 3 rects filled then four circles.
            framebuf_fill_rect(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int(r->w),
                    mp_obj_new_int(r->h-2*(int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            framebuf_fill_rect(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y),
                    mp_obj_new_int(r->w-2*(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            framebuf_fill_rect(6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int(r->w-2*(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a))
                }
            );
            if( r->rounding < 0.1f )
            {
                break;
            }
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(1),
                    mp_obj_new_int(0x02)  // top left
                }
            );
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+r->w-(int)r->rounding),
                    mp_obj_new_int(y0+r->y+(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(1),
                    mp_obj_new_int(0x01)  // top right
                }
            );
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(1),
                    mp_obj_new_int(0x04) // bottom left
                }
            );
            framebuf_ellipse(8,
                (mp_obj_t[8]){
                    fb_in, 
                    mp_obj_new_int(x0+r->x+r->w-(int)r->rounding),
                    mp_obj_new_int(y0+r->y+r->h-(int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int((int)r->rounding),
                    mp_obj_new_int(rgba_to_565(r->color.r, r->color.g, r->color.b, r->color.a)),
                    mp_obj_new_int(1),
                    mp_obj_new_int(0x08)  // bottom right
                }
            );
        } break;
        case NK_COMMAND_CIRCLE: {
            const struct nk_command_circle *c = (const struct nk_command_circle*)cmd;
            //nk_draw_list_stroke_circle(&ctx->draw_list, nk_vec2((float)c->x + (float)c->w/2,
            //    (float)c->y + (float)c->h/2), (float)c->w/2, c->color,
            //    config->circle_segment_count, c->line_thickness);
            //printf("circle %d %d %d %d\n", c->x, c->y, c->w, c->h);
            framebuf_ellipse(7,
                (mp_obj_t[7]){
                    fb_in, 
                    mp_obj_new_int(x0+c->x+c->w/2),
                    mp_obj_new_int(y0+c->y+c->h/2),
                    mp_obj_new_int(c->w/2),
                    mp_obj_new_int(c->h/2),
                    mp_obj_new_int(rgba_to_565(c->color.r, c->color.g, c->color.b, c->color.a)),
                    mp_obj_new_int(0)
                }
            );
        } break;
        case NK_COMMAND_CIRCLE_FILLED: {
            const struct nk_command_circle_filled *c = (const struct nk_command_circle_filled *)cmd;
            //nk_draw_list_fill_circle(&ctx->draw_list, nk_vec2((float)c->x + (float)c->w/2,
            //    (float)c->y + (float)c->h/2), (float)c->w/2, c->color,
            //    config->circle_segment_count);
            //printf("circle filled %d %d %d %d\n", c->x, c->y, c->w, c->h);
            framebuf_ellipse(7,
                (mp_obj_t[7]){
                    fb_in, 
                    mp_obj_new_int(x0+c->x+c->w/2),
                    mp_obj_new_int(y0+c->y+c->h/2),
                    mp_obj_new_int(c->w/2),
                    mp_obj_new_int(c->h/2),
                    mp_obj_new_int(rgba_to_565(c->color.r, c->color.g, c->color.b, c->color.a)),
                    mp_obj_new_int(1)
                }
            );
        } break;
        case NK_COMMAND_TEXT: {
            const struct nk_command_text *t = (const struct nk_command_text*)cmd;
            //nk_draw_list_add_text(&ctx->draw_list, t->font, nk_rect(t->x, t->y, t->w, t->h),
            //    t->string, t->length, t->height, t->foreground);
            //printf("text %d %d %d %d %s\n", t->x, t->y, t->w, t->h, t->string);
            framebuf_text(
                5, 
                (mp_obj_t[5]){
                    fb_in, 
                    mp_obj_new_str(t->string, t->length), 
                    mp_obj_new_int(x0+t->x), 
                    mp_obj_new_int(y0+t->y), 
                    mp_obj_new_int(rgba_to_565(t->foreground.r, t->foreground.g, t->foreground.b, t->foreground.a))
                }
            );
        } break;
        
        case NK_COMMAND_TRIANGLE: {
                const struct nk_command_triangle *t = (const struct nk_command_triangle*)cmd;
                /*
                struct nk_command_triangle {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i a;
    struct nk_vec2i b;
    struct nk_vec2i c;
    struct nk_color color;
};*/
            /*mp_obj_t array[] = {
                mp_obj_new_int( t->a.x ),
                mp_obj_new_int( t->a.y ),
                mp_obj_new_int( t->b.x ),
                mp_obj_new_int( t->b.y ),
                mp_obj_new_int( t->c.x ),
                mp_obj_new_int( t->c.y ),
            };*/
        mp_obj_array_t *array = m_new_obj(mp_obj_array_t);
        array->base.type = &mp_type_bytearray;
        array->typecode = 'h';
        array->len = 6;
        array->items = m_new(short, 6);
        short data[6] = {t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y};
        memcpy(array->items, data, sizeof(data));
            framebuf_poly(
                6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0), 
                    mp_obj_new_int(y0), 
                    array,
                    mp_obj_new_int(rgba_to_565(t->color.r, t->color.g, t->color.b, t->color.a)),
                    mp_obj_new_int(0)
                }
            );
            
        } break;
        case NK_COMMAND_TRIANGLE_FILLED: {
            const struct nk_command_triangle_filled *t = (const struct nk_command_triangle_filled*)cmd;
            /*mp_obj_t array[] = {
                mp_obj_new_int( t->a.x ),
                mp_obj_new_int( t->a.y ),
                mp_obj_new_int( t->b.x ),
                mp_obj_new_int( t->b.y ),
                mp_obj_new_int( t->c.x ),
                mp_obj_new_int( t->c.y ),
            };*/
        mp_obj_array_t *array = m_new_obj(mp_obj_array_t);
        array->base.type = &mp_type_bytearray;
        array->typecode = 'h';
        array->len = 6;
        array->items = m_new(short, 6);
        short data[6] = {t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y};
        memcpy(array->items, data, sizeof(data));
            framebuf_poly(
                6, 
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0), 
                    mp_obj_new_int(y0), 
                    array,
                    mp_obj_new_int(rgba_to_565(t->color.r, t->color.g, t->color.b, t->color.a)),
                    mp_obj_new_int(1)
                }
            );
        } break;
        
        
        case NK_COMMAND_IMAGE: {
            const struct nk_command_image *i = (const struct nk_command_image*)cmd;
            //nk_draw_list_add_image(&ctx->draw_list, i->img, nk_rect(i->x, i->y, i->w, i->h), i->col);
            //printf("image %d %d %d %d\n", i->x, i->y, i->w, i->h);
        } break;
        default: break;
        }
    }
    //nk_clear(ctx);
    
    return mp_const_none;
}


enum theme {THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK};

static void
set_style(struct nk_context *ctx, enum theme theme)
{
    struct nk_color table[NK_COLOR_COUNT];
    if (theme == THEME_WHITE) {
        table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_HEADER] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(185, 185, 185, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(170, 170, 170, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(120, 120, 120, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_EDIT] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
        table[NK_COLOR_COMBO] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(180, 180, 180, 255);
        nk_style_from_table(ctx, table);
    } else if (theme == THEME_RED) {
        table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
        table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
        table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
        nk_style_from_table(ctx, table);
    } else if (theme == THEME_BLUE) {
        table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
        table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
        table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
        table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
        nk_style_from_table(ctx, table);
    } else if (theme == THEME_DARK) {
        table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
        table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
        table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
        nk_style_from_table(ctx, table);
    } else {
        nk_style_default(ctx);
    }
}

STATIC mp_obj_t Nk_set_style(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum theme t = (enum theme)mp_obj_get_int( args_in[1] );
    set_style(ctx, t);
    return mp_const_none;
}

STATIC mp_obj_t Nk_clear(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_clear(ctx);
    return mp_const_none;
}



STATIC mp_obj_t Nk_input_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_input_begin(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_input_motion(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    int x = mp_obj_get_int( args_in[1] );
    int y = mp_obj_get_int( args_in[2] );
    nk_input_motion(ctx, x, y);
    return mp_const_none;
}

STATIC mp_obj_t Nk_input_button(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_buttons id = mp_obj_get_int( args_in[1] );
    int x = mp_obj_get_int( args_in[2] );
    int y = mp_obj_get_int( args_in[3] );
    nk_bool down = mp_obj_get_int( args_in[4] );
    nk_input_button(ctx, id, x, y, down);
    return mp_const_none;
}

STATIC mp_obj_t Nk_input_char(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char c = mp_obj_get_int( args_in[1] );
    nk_input_char(ctx, c);
    return mp_const_none;
}

STATIC mp_obj_t Nk_input_key(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_keys key = mp_obj_get_int( args_in[1] );
    nk_bool down = mp_obj_get_int( args_in[2] );
    nk_input_key(ctx, key, down);
    return mp_const_none;
}

STATIC mp_obj_t Nk_input_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_input_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*title = mp_obj_str_get_str( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    struct nk_rect bounds = {
        mp_obj_get_float(arg_2[0]),
        mp_obj_get_float(arg_2[1]),
        mp_obj_get_float(arg_2[2]),
        mp_obj_get_float(arg_2[3])
    };
    nk_flags flags = mp_obj_get_int( args_in[3] );
    nk_bool retval = nk_begin(ctx, title, bounds, flags);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_button_color(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    struct nk_color color = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    nk_bool retval = nk_button_color(ctx, color);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_button_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*title = mp_obj_str_get_str( args_in[1] );
    nk_bool retval = nk_button_label(ctx, title);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_button_set_behavior(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_button_behavior behavior = mp_obj_get_int( args_in[1] );
    nk_button_set_behavior(ctx, behavior);
    return mp_const_none;
}

STATIC mp_obj_t Nk_button_symbol(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_symbol_type symbol = mp_obj_get_int( args_in[1] );
    nk_bool retval = nk_button_symbol(ctx, symbol);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_button_symbol_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_symbol_type symbol = mp_obj_get_int( args_in[1] );
    char*label = mp_obj_str_get_str( args_in[2] );
    nk_flags align = mp_obj_get_int( args_in[3] );
    nk_bool retval = nk_button_symbol_label(ctx, symbol, label, align);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_chart_add_slot(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_chart_type type = mp_obj_get_int( args_in[1] );
    int count = mp_obj_get_int( args_in[2] );
    float min_value = mp_obj_get_float( args_in[3] );
    float max_value = mp_obj_get_float( args_in[4] );
    nk_chart_add_slot(ctx, type, count, min_value, max_value);
    return mp_const_none;
}

STATIC mp_obj_t Nk_chart_add_slot_colored(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 7, 7, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_chart_type type = mp_obj_get_int( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    struct nk_color color = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    mp_obj_t *arg_3 = NULL;
    size_t arg_3_len = 0;
    mp_obj_get_array(args_in[3], &arg_3_len, &arg_3);
    struct nk_color highlight = {
        mp_obj_get_int(arg_3[0]),
        mp_obj_get_int(arg_3[1]),
        mp_obj_get_int(arg_3[2]),
        mp_obj_get_int(arg_3[3])
    };
    int count = mp_obj_get_int( args_in[4] );
    float min_value = mp_obj_get_float( args_in[5] );
    float max_value = mp_obj_get_float( args_in[6] );
    nk_chart_add_slot_colored(ctx, type, color, highlight, count, min_value, max_value);
    return mp_const_none;
}

STATIC mp_obj_t Nk_chart_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_chart_type type = mp_obj_get_int( args_in[1] );
    int count = mp_obj_get_int( args_in[2] );
    float min_value = mp_obj_get_float( args_in[3] );
    float max_value = mp_obj_get_float( args_in[4] );
    nk_bool retval = nk_chart_begin(ctx, type, count, min_value, max_value);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_chart_begin_colored(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 7, 7, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_chart_type type = mp_obj_get_int( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    struct nk_color color = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    mp_obj_t *arg_3 = NULL;
    size_t arg_3_len = 0;
    mp_obj_get_array(args_in[3], &arg_3_len, &arg_3);
    struct nk_color highlight = {
        mp_obj_get_int(arg_3[0]),
        mp_obj_get_int(arg_3[1]),
        mp_obj_get_int(arg_3[2]),
        mp_obj_get_int(arg_3[3])
    };
    int count = mp_obj_get_int( args_in[4] );
    float min_value = mp_obj_get_float( args_in[5] );
    float max_value = mp_obj_get_float( args_in[6] );
    nk_bool retval = nk_chart_begin_colored(ctx, type, color, highlight, count, min_value, max_value);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_chart_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_chart_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_chart_push(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float value = mp_obj_get_float( args_in[1] );
    nk_flags retval = nk_chart_push(ctx, value);
    return mp_obj_new_int( retval );
}

STATIC mp_obj_t Nk_chart_push_slot(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float value = mp_obj_get_float( args_in[1] );
    int slot = mp_obj_get_int( args_in[2] );
    nk_flags retval = nk_chart_push_slot(ctx, value, slot);
    return mp_obj_new_int( retval );
}

STATIC mp_obj_t Nk_checkbox_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    nk_bool* active = (nk_bool*) mp_obj_get_int( args_in[2] );
    nk_bool retval = nk_checkbox_label(ctx, label, active);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_color_pick(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    struct nk_colorf* color = (struct nk_colorf*) mp_obj_get_int( args_in[1] );
    enum nk_color_format fmt = mp_obj_get_int( args_in[2] );
    nk_bool retval = nk_color_pick(ctx, color, fmt);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_color_picker(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    struct nk_colorf color = {
        mp_obj_get_float(arg_1[0]),
        mp_obj_get_float(arg_1[1]),
        mp_obj_get_float(arg_1[2]),
        mp_obj_get_float(arg_1[3])
    };
    enum nk_color_format fmt = mp_obj_get_int( args_in[2] );
    struct nk_colorf retval = nk_color_picker(ctx, color, fmt);
    mp_obj_t tuple[] = {
        mp_obj_new_float( retval.r ),
        mp_obj_new_float( retval.g ),
        mp_obj_new_float( retval.b ),
        mp_obj_new_float( retval.a )
    };
    return mp_obj_new_tuple( 4, tuple );
}

STATIC mp_obj_t Nk_combo(size_t n_args, const mp_obj_t *args_in)
{
    printf( " Not implemented: nk_combo\n " );
    return mp_const_none;
}

STATIC mp_obj_t Nk_combo_begin_color(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    struct nk_color color = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    struct nk_vec2 size = {
        mp_obj_get_float(arg_2[0]),
        mp_obj_get_float(arg_2[1])
    };
    nk_bool retval = nk_combo_begin_color(ctx, color, size);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_combo_begin_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*selected = mp_obj_str_get_str( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    struct nk_vec2 size = {
        mp_obj_get_float(arg_2[0]),
        mp_obj_get_float(arg_2[1])
    };
    nk_bool retval = nk_combo_begin_label(ctx, selected, size);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_combo_close(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_combo_close(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_combo_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_combo_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_contextual_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_flags flags = mp_obj_get_int( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    struct nk_vec2 size = {
        mp_obj_get_float(arg_2[0]),
        mp_obj_get_float(arg_2[1])
    };
    mp_obj_t *arg_3 = NULL;
    size_t arg_3_len = 0;
    mp_obj_get_array(args_in[3], &arg_3_len, &arg_3);
    struct nk_rect trigger_bounds = {
        mp_obj_get_float(arg_3[0]),
        mp_obj_get_float(arg_3[1]),
        mp_obj_get_float(arg_3[2]),
        mp_obj_get_float(arg_3[3])
    };
    nk_bool retval = nk_contextual_begin(ctx, flags, size, trigger_bounds);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_contextual_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_contextual_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_contextual_item_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    nk_flags align = mp_obj_get_int( args_in[2] );
    nk_bool retval = nk_contextual_item_label(ctx, label, align);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_edit_string(size_t n_args, const mp_obj_t *args_in)
{
    printf( " Not implemented: nk_edit_string\n " );
    return mp_const_none;
}

STATIC mp_obj_t Nk_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_group_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*title = mp_obj_str_get_str( args_in[1] );
    nk_flags flags = mp_obj_get_int( args_in[2] );
    nk_bool retval = nk_group_begin(ctx, title, flags);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_group_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_group_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*str = mp_obj_str_get_str( args_in[1] );
    nk_flags alignment = mp_obj_get_int( args_in[2] );
    nk_label(ctx, str, alignment);
    return mp_const_none;
}

STATIC mp_obj_t Nk_label_colored(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*str = mp_obj_str_get_str( args_in[1] );
    nk_flags align = mp_obj_get_int( args_in[2] );
    mp_obj_t *arg_3 = NULL;
    size_t arg_3_len = 0;
    mp_obj_get_array(args_in[3], &arg_3_len, &arg_3);
    struct nk_color color = {
        mp_obj_get_int(arg_3[0]),
        mp_obj_get_int(arg_3[1]),
        mp_obj_get_int(arg_3[2]),
        mp_obj_get_int(arg_3[3])
    };
    nk_label_colored(ctx, str, align, color);
    return mp_const_none;
}

STATIC mp_obj_t Nk_label_wrap(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*str = mp_obj_str_get_str( args_in[1] );
    nk_label_wrap(ctx, str);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_layout_format fmt = mp_obj_get_int( args_in[1] );
    float height = mp_obj_get_float( args_in[2] );
    int cols = mp_obj_get_int( args_in[3] );
    float* ratio = (float*) mp_obj_get_int( args_in[4] );
    nk_layout_row(ctx, fmt, height, cols, ratio);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_layout_format fmt = mp_obj_get_int( args_in[1] );
    float row_height = mp_obj_get_float( args_in[2] );
    int cols = mp_obj_get_int( args_in[3] );
    nk_layout_row_begin(ctx, fmt, row_height, cols);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_dynamic(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float height = mp_obj_get_float( args_in[1] );
    int cols = mp_obj_get_int( args_in[2] );
    nk_layout_row_dynamic(ctx, height, cols);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_layout_row_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_push(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float ratio_or_width = mp_obj_get_float( args_in[1] );
    nk_layout_row_push(ctx, ratio_or_width);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_static(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float height = mp_obj_get_float( args_in[1] );
    int item_width = mp_obj_get_int( args_in[2] );
    int cols = mp_obj_get_int( args_in[3] );
    nk_layout_row_static(ctx, height, item_width, cols);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_template_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float height = mp_obj_get_float( args_in[1] );
    nk_layout_row_template_begin(ctx, height);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_template_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_layout_row_template_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_template_push_dynamic(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_layout_row_template_push_dynamic(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_template_push_static(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float width = mp_obj_get_float( args_in[1] );
    nk_layout_row_template_push_static(ctx, width);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_row_template_push_variable(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float min_width = mp_obj_get_float( args_in[1] );
    nk_layout_row_template_push_variable(ctx, min_width);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_space_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_layout_format fmt = mp_obj_get_int( args_in[1] );
    float height = mp_obj_get_float( args_in[2] );
    int widget_count = mp_obj_get_int( args_in[3] );
    nk_layout_space_begin(ctx, fmt, height, widget_count);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_space_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_layout_space_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_layout_space_push(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    struct nk_rect rect = {
        mp_obj_get_float(arg_1[0]),
        mp_obj_get_float(arg_1[1]),
        mp_obj_get_float(arg_1[2]),
        mp_obj_get_float(arg_1[3])
    };
    nk_layout_space_push(ctx, rect);
    return mp_const_none;
}

STATIC mp_obj_t Nk_menu_begin_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*text = mp_obj_str_get_str( args_in[1] );
    nk_flags align = mp_obj_get_int( args_in[2] );
    mp_obj_t *arg_3 = NULL;
    size_t arg_3_len = 0;
    mp_obj_get_array(args_in[3], &arg_3_len, &arg_3);
    struct nk_vec2 size = {
        mp_obj_get_float(arg_3[0]),
        mp_obj_get_float(arg_3[1])
    };
    nk_bool retval = nk_menu_begin_label(ctx, text, align, size);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_menu_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_menu_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_menu_item_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    nk_flags align = mp_obj_get_int( args_in[2] );
    nk_bool retval = nk_menu_item_label(ctx, label, align);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_menubar_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_menubar_begin(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_menubar_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_menubar_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_option_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    nk_bool active = mp_obj_get_int( args_in[2] );
    nk_bool retval = nk_option_label(ctx, label, active);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_plot(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_chart_type type = mp_obj_get_int( args_in[1] );
    float* values = (float*) mp_obj_get_int( args_in[2] );
    int count = mp_obj_get_int( args_in[3] );
    int offset = mp_obj_get_int( args_in[4] );
    nk_plot(ctx, type, values, count, offset);
    return mp_const_none;
}

STATIC mp_obj_t Nk_popup_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_popup_type type = mp_obj_get_int( args_in[1] );
    char*title = mp_obj_str_get_str( args_in[2] );
    nk_flags flags = mp_obj_get_int( args_in[3] );
    mp_obj_t *arg_4 = NULL;
    size_t arg_4_len = 0;
    mp_obj_get_array(args_in[4], &arg_4_len, &arg_4);
    struct nk_rect rect = {
        mp_obj_get_float(arg_4[0]),
        mp_obj_get_float(arg_4[1]),
        mp_obj_get_float(arg_4[2]),
        mp_obj_get_float(arg_4[3])
    };
    nk_bool retval = nk_popup_begin(ctx, type, title, flags, rect);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_popup_close(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_popup_close(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_popup_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_popup_end(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_prog(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_size cur = mp_obj_get_int( args_in[1] );
    nk_size max = mp_obj_get_int( args_in[2] );
    nk_bool modifyable = mp_obj_get_int( args_in[3] );
    nk_size retval = nk_prog(ctx, cur, max, modifyable);
    return mp_obj_new_int( retval );
}

STATIC mp_obj_t Nk_progress(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_size* cur = (nk_size*) mp_obj_get_int( args_in[1] );
    nk_size max = mp_obj_get_int( args_in[2] );
    nk_bool is_modifyable = mp_obj_get_int( args_in[3] );
    nk_bool retval = nk_progress(ctx, cur, max, is_modifyable);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_property_float(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 7, 7, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    float min = mp_obj_get_float( args_in[2] );
    float* val = (float*) mp_obj_get_int( args_in[3] );
    float max = mp_obj_get_float( args_in[4] );
    float step = mp_obj_get_float( args_in[5] );
    float inc_per_pixel = mp_obj_get_float( args_in[6] );
    nk_property_float(ctx, name, min, val, max, step, inc_per_pixel);
    return mp_const_none;
}

STATIC mp_obj_t Nk_property_int(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 7, 7, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    int min = mp_obj_get_int( args_in[2] );
    int* val = (int*) mp_obj_get_int( args_in[3] );
    int max = mp_obj_get_int( args_in[4] );
    int step = mp_obj_get_int( args_in[5] );
    float inc_per_pixel = mp_obj_get_float( args_in[6] );
    nk_property_int(ctx, name, min, val, max, step, inc_per_pixel);
    return mp_const_none;
}

STATIC mp_obj_t Nk_propertyf(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 7, 7, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    float min = mp_obj_get_float( args_in[2] );
    float val = mp_obj_get_float( args_in[3] );
    float max = mp_obj_get_float( args_in[4] );
    float step = mp_obj_get_float( args_in[5] );
    float inc_per_pixel = mp_obj_get_float( args_in[6] );
    float retval = nk_propertyf(ctx, name, min, val, max, step, inc_per_pixel);
    return mp_obj_new_float( retval );
}

STATIC mp_obj_t Nk_propertyi(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 7, 7, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    int min = mp_obj_get_int( args_in[2] );
    int val = mp_obj_get_int( args_in[3] );
    int max = mp_obj_get_int( args_in[4] );
    int step = mp_obj_get_int( args_in[5] );
    float inc_per_pixel = mp_obj_get_float( args_in[6] );
    int retval = nk_propertyi(ctx, name, min, val, max, step, inc_per_pixel);
    return mp_obj_new_int( retval );
}

STATIC mp_obj_t Nk_selectable_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*str = mp_obj_str_get_str( args_in[1] );
    nk_flags align = mp_obj_get_int( args_in[2] );
    nk_bool* value = (nk_bool*) mp_obj_get_int( args_in[3] );
    nk_bool retval = nk_selectable_label(ctx, str, align, value);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_selectable_symbol_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_symbol_type sym = mp_obj_get_int( args_in[1] );
    char*title = mp_obj_str_get_str( args_in[2] );
    nk_flags align = mp_obj_get_int( args_in[3] );
    nk_bool* value = (nk_bool*) mp_obj_get_int( args_in[4] );
    nk_bool retval = nk_selectable_symbol_label(ctx, sym, title, align, value);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_slide_int(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    int min = mp_obj_get_int( args_in[1] );
    int val = mp_obj_get_int( args_in[2] );
    int max = mp_obj_get_int( args_in[3] );
    int step = mp_obj_get_int( args_in[4] );
    int retval = nk_slide_int(ctx, min, val, max, step);
    return mp_obj_new_int( retval );
}

STATIC mp_obj_t Nk_slider_float(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    float min_value = mp_obj_get_float( args_in[1] );
    float* value = (float*) mp_obj_get_int( args_in[2] );
    float max_value = mp_obj_get_float( args_in[3] );
    float value_step = mp_obj_get_float( args_in[4] );
    nk_bool retval = nk_slider_float(ctx, min_value, value, max_value, value_step);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_slider_int(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    int min = mp_obj_get_int( args_in[1] );
    int* val = (int*) mp_obj_get_int( args_in[2] );
    int max = mp_obj_get_int( args_in[3] );
    int step = mp_obj_get_int( args_in[4] );
    nk_bool retval = nk_slider_int(ctx, min, val, max, step);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_spacing(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    int cols = mp_obj_get_int( args_in[1] );
    nk_spacing(ctx, cols);
    return mp_const_none;
}

STATIC mp_obj_t Nk_text(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*str = mp_obj_str_get_str( args_in[1] );
    int len = mp_obj_get_int( args_in[2] );
    nk_flags alignment = mp_obj_get_int( args_in[3] );
    nk_text(ctx, str, len, alignment);
    return mp_const_none;
}

STATIC mp_obj_t Nk_tooltip(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*text = mp_obj_str_get_str( args_in[1] );
    nk_tooltip(ctx, text);
    return mp_const_none;
}

STATIC mp_obj_t Nk_tree_element_pop(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_tree_element_pop(ctx);
    return mp_const_none;
}

STATIC mp_obj_t Nk_tree_state_push(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_tree_type type = mp_obj_get_int( args_in[1] );
    char*title = mp_obj_str_get_str( args_in[2] );
    enum nk_collapse_states* state = mp_obj_get_int( args_in[3] );
    nk_bool retval = nk_tree_state_push(ctx, type, title, state);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_widget(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    struct nk_rect* bounds = (struct nk_rect*) mp_obj_get_int( args_in[0] );
    struct nk_context *ctx = MP_OBJ_TO_PTR( args_in[1] );
    enum nk_widget_layout_states retval = nk_widget(bounds, ctx);
    return mp_obj_new_int( retval );
}

STATIC mp_obj_t Nk_widget_bounds(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    struct nk_rect retval = nk_widget_bounds(ctx);
    mp_obj_t tuple[] = {
        mp_obj_new_float( retval.x ),
        mp_obj_new_float( retval.y ),
        mp_obj_new_float( retval.w ),
        mp_obj_new_float( retval.h )
    };
    return mp_obj_new_tuple( 4, tuple );
}

STATIC mp_obj_t Nk_window_is_closed(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    nk_bool retval = nk_window_is_closed(ctx, name);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_tree_push(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    enum nk_tree_type type = mp_obj_get_int( args_in[1] );
    char*title = mp_obj_str_get_str( args_in[2] );
    enum nk_collapse_states initial_state = mp_obj_get_int( args_in[3] );
    nk_bool retval = nk_tree_push(ctx, type, title, initial_state);
    return mp_obj_new_bool( retval );
}

STATIC mp_obj_t Nk_tree_pop(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tNk *self = MP_OBJ_TO_PTR( args_in[0] );
    struct nk_context* ctx = &self->ctx;
    nk_tree_pop(ctx);
    return mp_const_none;
}


/****************************************************************************
 * Public Functions Definitions.
 ****************************************************************************/