/****************************************************************************
 * File:	modmicroui.c
 * Brief:		

integration steps:
1.
file: mpconfigport.h
line: // extra built in modules to add to the list
add : extern const struct _mp_obj_module_t microui_module;
2.
file: mpconfigport.h
line: // #define MICROPY_PORT_BUILTIN_MODULES
add : { MP_ROM_QSTR(MP_QSTR_microui), (mp_obj_t)&microui_module }, 
3.
file: makefile.mk
line: // SRC_C =  
add : modmicroui.c 

 * Author:		
 ****************************************************************************/
/****************************************************************************
 * Private Includes.
 ****************************************************************************/
#include    <stdio.h>
#include    <string.h>
#include	"py/obj.h"
#include	"py/runtime.h"
#include	"microui.h"

/****************************************************************************
 * Private Defines.
 ****************************************************************************/
/*MP_DEFINE_CONST_OBJ_TYPE(
    microui_type,
    MP_QSTR_microui,
    MP_TYPE_FLAG_NONE,
    make_new, microui_make_new,
    print, microui_print,
    locals_dict, &microui_locals_dict
);*/
MP_REGISTER_MODULE(MP_QSTR_microui, microui_module );

/****************************************************************************
 * Private Types.
 ****************************************************************************/
typedef struct sMicroui tMicroui;
struct sMicroui
{
    mp_obj_base_t base;
    mu_Context ctx;
};

/****************************************************************************
 * Private Functions Declarations.
 ****************************************************************************/
static mp_obj_t microui_make_new( const mp_obj_type_t *type_in, size_t n_args, size_t n_kw, const mp_obj_t *args );
static void microui_print( const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind );
static mp_obj_t Mu_vec2(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_rect(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_color(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_init(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_end(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_set_focus(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_get_id(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_push_id(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_pop_id(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_push_clip_rect(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_pop_clip_rect(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_get_clip_rect(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_check_clip(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_get_current_container(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_get_container(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_bring_to_front(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_pool_init(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_pool_get(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_pool_update(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_mousemove(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_mousedown(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_mouseup(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_scroll(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_keydown(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_keyup(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_input_text(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_push_command(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_next_command(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_set_clip(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_rect(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_box(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_text(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_icon(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_row(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_width(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_height(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_begin_column(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_end_column(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_set_next(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_layout_next(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_control_frame(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_control_text(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_mouse_over(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_update_control(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_button(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_textbox(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_slider(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_number(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_header(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_treenode(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_window(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_panel(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_text(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_label(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_button_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_checkbox(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_textbox_raw(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_textbox_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_slider_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_number_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_header_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_treenode_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_end_treenode(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_window_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_end_window(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_open_popup(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_popup(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_end_popup(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_begin_panel_ex(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_end_panel(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw(size_t n_args, const mp_obj_t *args_in);
//static mp_obj_t Mu_draw_line_fast(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_draw_line_fast_fb(size_t n_args, const mp_obj_t *args_in);
static mp_obj_t Mu_set_style(size_t n_args, const mp_obj_t *args_in);



/****************************************************************************
 * Private Variables Declarations.
 ****************************************************************************/
static const mp_obj_fun_builtin_var_t Mu_vec2_obj;
static const mp_obj_fun_builtin_var_t Mu_rect_obj;
static const mp_obj_fun_builtin_var_t Mu_color_obj;
static const mp_obj_fun_builtin_var_t Mu_init_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_obj;
static const mp_obj_fun_builtin_var_t Mu_end_obj;
static const mp_obj_fun_builtin_var_t Mu_set_focus_obj;
static const mp_obj_fun_builtin_var_t Mu_get_id_obj;
static const mp_obj_fun_builtin_var_t Mu_push_id_obj;
static const mp_obj_fun_builtin_var_t Mu_pop_id_obj;
static const mp_obj_fun_builtin_var_t Mu_push_clip_rect_obj;
static const mp_obj_fun_builtin_var_t Mu_pop_clip_rect_obj;
static const mp_obj_fun_builtin_var_t Mu_get_clip_rect_obj;
static const mp_obj_fun_builtin_var_t Mu_check_clip_obj;
static const mp_obj_fun_builtin_var_t Mu_get_current_container_obj;
static const mp_obj_fun_builtin_var_t Mu_get_container_obj;
static const mp_obj_fun_builtin_var_t Mu_bring_to_front_obj;
static const mp_obj_fun_builtin_var_t Mu_pool_init_obj;
static const mp_obj_fun_builtin_var_t Mu_pool_get_obj;
static const mp_obj_fun_builtin_var_t Mu_pool_update_obj;
static const mp_obj_fun_builtin_var_t Mu_input_mousemove_obj;
static const mp_obj_fun_builtin_var_t Mu_input_mousedown_obj;
static const mp_obj_fun_builtin_var_t Mu_input_mouseup_obj;
static const mp_obj_fun_builtin_var_t Mu_input_scroll_obj;
static const mp_obj_fun_builtin_var_t Mu_input_keydown_obj;
static const mp_obj_fun_builtin_var_t Mu_input_keyup_obj;
static const mp_obj_fun_builtin_var_t Mu_input_text_obj;
static const mp_obj_fun_builtin_var_t Mu_push_command_obj;
static const mp_obj_fun_builtin_var_t Mu_next_command_obj;
static const mp_obj_fun_builtin_var_t Mu_set_clip_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_rect_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_box_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_text_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_icon_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_row_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_width_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_height_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_begin_column_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_end_column_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_set_next_obj;
static const mp_obj_fun_builtin_var_t Mu_layout_next_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_control_frame_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_control_text_obj;
static const mp_obj_fun_builtin_var_t Mu_mouse_over_obj;
static const mp_obj_fun_builtin_var_t Mu_update_control_obj;
static const mp_obj_fun_builtin_var_t Mu_button_obj;
static const mp_obj_fun_builtin_var_t Mu_textbox_obj;
static const mp_obj_fun_builtin_var_t Mu_slider_obj;
static const mp_obj_fun_builtin_var_t Mu_number_obj;
static const mp_obj_fun_builtin_var_t Mu_header_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_treenode_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_window_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_panel_obj;
static const mp_obj_fun_builtin_var_t Mu_text_obj;
static const mp_obj_fun_builtin_var_t Mu_label_obj;
static const mp_obj_fun_builtin_var_t Mu_button_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_checkbox_obj;
static const mp_obj_fun_builtin_var_t Mu_textbox_raw_obj;
static const mp_obj_fun_builtin_var_t Mu_textbox_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_slider_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_number_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_header_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_treenode_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_end_treenode_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_window_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_end_window_obj;
static const mp_obj_fun_builtin_var_t Mu_open_popup_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_popup_obj;
static const mp_obj_fun_builtin_var_t Mu_end_popup_obj;
static const mp_obj_fun_builtin_var_t Mu_begin_panel_ex_obj;
static const mp_obj_fun_builtin_var_t Mu_end_panel_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_obj;
//static const mp_obj_fun_builtin_var_t Mu_draw_line_fast_obj;
static const mp_obj_fun_builtin_var_t Mu_draw_line_fast_fb_obj;
static const mp_obj_fun_builtin_var_t Mu_set_style_obj;

const mp_rom_map_elem_t microui_locals_dict_table[];
static const mp_obj_dict_t microui_locals_dict;
const mp_map_elem_t microui_globals_table[];
static const mp_obj_dict_t microui_globals;
const mp_obj_module_t microui_module;

/****************************************************************************
 * Private Variables Definitions.
 ****************************************************************************/
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_vec2_obj, 2, 2, Mu_vec2 );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_rect_obj, 4, 4, Mu_rect );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_color_obj, 4, 4, Mu_color );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_init_obj, 1, 1, Mu_init );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_obj, 1, 1, Mu_begin );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_end_obj, 1, 1, Mu_end );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_set_focus_obj, 2, 2, Mu_set_focus );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_get_id_obj, 3, 3, Mu_get_id );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_push_id_obj, 3, 3, Mu_push_id );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_pop_id_obj, 1, 1, Mu_pop_id );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_push_clip_rect_obj, 2, 2, Mu_push_clip_rect );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_pop_clip_rect_obj, 1, 1, Mu_pop_clip_rect );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_get_clip_rect_obj, 1, 1, Mu_get_clip_rect );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_check_clip_obj, 2, 2, Mu_check_clip );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_get_current_container_obj, 1, 1, Mu_get_current_container );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_get_container_obj, 2, 2, Mu_get_container );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_bring_to_front_obj, 2, 2, Mu_bring_to_front );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_pool_init_obj, 4, 4, Mu_pool_init );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_pool_get_obj, 4, 4, Mu_pool_get );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_pool_update_obj, 3, 3, Mu_pool_update );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_mousemove_obj, 3, 3, Mu_input_mousemove );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_mousedown_obj, 4, 4, Mu_input_mousedown );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_mouseup_obj, 4, 4, Mu_input_mouseup );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_scroll_obj, 3, 3, Mu_input_scroll );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_keydown_obj, 2, 2, Mu_input_keydown );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_keyup_obj, 2, 2, Mu_input_keyup );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_input_text_obj, 2, 2, Mu_input_text );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_push_command_obj, 3, 3, Mu_push_command );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_next_command_obj, 2, 2, Mu_next_command );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_set_clip_obj, 2, 2, Mu_set_clip );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_rect_obj, 3, 3, Mu_draw_rect );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_box_obj, 3, 3, Mu_draw_box );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_text_obj, 6, 6, Mu_draw_text );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_icon_obj, 4, 4, Mu_draw_icon );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_row_obj, 3, 3, Mu_layout_row );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_width_obj, 2, 2, Mu_layout_width );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_height_obj, 2, 2, Mu_layout_height );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_begin_column_obj, 1, 1, Mu_layout_begin_column );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_end_column_obj, 1, 1, Mu_layout_end_column );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_set_next_obj, 3, 3, Mu_layout_set_next );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_layout_next_obj, 1, 1, Mu_layout_next );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_control_frame_obj, 5, 5, Mu_draw_control_frame );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_control_text_obj, 5, 5, Mu_draw_control_text );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_mouse_over_obj, 2, 2, Mu_mouse_over );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_update_control_obj, 4, 4, Mu_update_control );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_button_obj, 2, 2, Mu_button );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_textbox_obj, 3, 3, Mu_textbox );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_slider_obj, 5, 5, Mu_slider );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_number_obj, 3, 3, Mu_number );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_header_obj, 2, 2, Mu_header );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_treenode_obj, 2, 2, Mu_begin_treenode );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_window_obj, 3, 3, Mu_begin_window );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_panel_obj, 2, 2, Mu_begin_panel );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_text_obj, 2, 2, Mu_text );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_label_obj, 2, 2, Mu_label );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_button_ex_obj, 4, 4, Mu_button_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_checkbox_obj, 3, 3, Mu_checkbox );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_textbox_raw_obj, 6, 6, Mu_textbox_raw );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_textbox_ex_obj, 4, 4, Mu_textbox_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_slider_ex_obj, 8, 8, Mu_slider_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_number_ex_obj, 5, 5, Mu_number_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_header_ex_obj, 3, 3, Mu_header_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_treenode_ex_obj, 3, 3, Mu_begin_treenode_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_end_treenode_obj, 1, 1, Mu_end_treenode );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_window_ex_obj, 4, 4, Mu_begin_window_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_end_window_obj, 1, 1, Mu_end_window );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_open_popup_obj, 2, 2, Mu_open_popup );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_popup_obj, 2, 2, Mu_begin_popup );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_end_popup_obj, 1, 1, Mu_end_popup );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_begin_panel_ex_obj, 3, 3, Mu_begin_panel_ex );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_end_panel_obj, 1, 1, Mu_end_panel );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_obj, 4, 4, Mu_draw );
//static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_line_fast_obj, 3, 3, Mu_draw_line_fast );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_draw_line_fast_fb_obj, 6, 6, Mu_draw_line_fast_fb );
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN( Mu_set_style_obj, 2, 2, Mu_set_style );

const mp_rom_map_elem_t microui_locals_dict_table[] = 
{
    { MP_ROM_QSTR( MP_QSTR_vec2 ), MP_ROM_PTR( &Mu_vec2_obj) },
    { MP_ROM_QSTR( MP_QSTR_rect ), MP_ROM_PTR( &Mu_rect_obj) },
    { MP_ROM_QSTR( MP_QSTR_color ), MP_ROM_PTR( &Mu_color_obj) },
    { MP_ROM_QSTR( MP_QSTR_init ), MP_ROM_PTR( &Mu_init_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin ), MP_ROM_PTR( &Mu_begin_obj) },
    { MP_ROM_QSTR( MP_QSTR_end ), MP_ROM_PTR( &Mu_end_obj) },
    { MP_ROM_QSTR( MP_QSTR_set_focus ), MP_ROM_PTR( &Mu_set_focus_obj) },
    { MP_ROM_QSTR( MP_QSTR_get_id ), MP_ROM_PTR( &Mu_get_id_obj) },
    { MP_ROM_QSTR( MP_QSTR_push_id ), MP_ROM_PTR( &Mu_push_id_obj) },
    { MP_ROM_QSTR( MP_QSTR_pop_id ), MP_ROM_PTR( &Mu_pop_id_obj) },
    { MP_ROM_QSTR( MP_QSTR_push_clip_rect ), MP_ROM_PTR( &Mu_push_clip_rect_obj) },
    { MP_ROM_QSTR( MP_QSTR_pop_clip_rect ), MP_ROM_PTR( &Mu_pop_clip_rect_obj) },
    { MP_ROM_QSTR( MP_QSTR_get_clip_rect ), MP_ROM_PTR( &Mu_get_clip_rect_obj) },
    { MP_ROM_QSTR( MP_QSTR_check_clip ), MP_ROM_PTR( &Mu_check_clip_obj) },
    { MP_ROM_QSTR( MP_QSTR_get_current_container ), MP_ROM_PTR( &Mu_get_current_container_obj) },
    { MP_ROM_QSTR( MP_QSTR_get_container ), MP_ROM_PTR( &Mu_get_container_obj) },
    { MP_ROM_QSTR( MP_QSTR_bring_to_front ), MP_ROM_PTR( &Mu_bring_to_front_obj) },
    { MP_ROM_QSTR( MP_QSTR_pool_init ), MP_ROM_PTR( &Mu_pool_init_obj) },
    { MP_ROM_QSTR( MP_QSTR_pool_get ), MP_ROM_PTR( &Mu_pool_get_obj) },
    { MP_ROM_QSTR( MP_QSTR_pool_update ), MP_ROM_PTR( &Mu_pool_update_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_mousemove ), MP_ROM_PTR( &Mu_input_mousemove_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_mousedown ), MP_ROM_PTR( &Mu_input_mousedown_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_mouseup ), MP_ROM_PTR( &Mu_input_mouseup_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_scroll ), MP_ROM_PTR( &Mu_input_scroll_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_keydown ), MP_ROM_PTR( &Mu_input_keydown_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_keyup ), MP_ROM_PTR( &Mu_input_keyup_obj) },
    { MP_ROM_QSTR( MP_QSTR_input_text ), MP_ROM_PTR( &Mu_input_text_obj) },
    { MP_ROM_QSTR( MP_QSTR_push_command ), MP_ROM_PTR( &Mu_push_command_obj) },
    { MP_ROM_QSTR( MP_QSTR_next_command ), MP_ROM_PTR( &Mu_next_command_obj) },
    { MP_ROM_QSTR( MP_QSTR_set_clip ), MP_ROM_PTR( &Mu_set_clip_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_rect ), MP_ROM_PTR( &Mu_draw_rect_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_box ), MP_ROM_PTR( &Mu_draw_box_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_text ), MP_ROM_PTR( &Mu_draw_text_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_icon ), MP_ROM_PTR( &Mu_draw_icon_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_row ), MP_ROM_PTR( &Mu_layout_row_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_width ), MP_ROM_PTR( &Mu_layout_width_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_height ), MP_ROM_PTR( &Mu_layout_height_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_begin_column ), MP_ROM_PTR( &Mu_layout_begin_column_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_end_column ), MP_ROM_PTR( &Mu_layout_end_column_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_set_next ), MP_ROM_PTR( &Mu_layout_set_next_obj) },
    { MP_ROM_QSTR( MP_QSTR_layout_next ), MP_ROM_PTR( &Mu_layout_next_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_control_frame ), MP_ROM_PTR( &Mu_draw_control_frame_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_control_text ), MP_ROM_PTR( &Mu_draw_control_text_obj) },
    { MP_ROM_QSTR( MP_QSTR_mouse_over ), MP_ROM_PTR( &Mu_mouse_over_obj) },
    { MP_ROM_QSTR( MP_QSTR_update_control ), MP_ROM_PTR( &Mu_update_control_obj) },
    { MP_ROM_QSTR( MP_QSTR_button ), MP_ROM_PTR( &Mu_button_obj) },
    { MP_ROM_QSTR( MP_QSTR_textbox ), MP_ROM_PTR( &Mu_textbox_obj) },
    { MP_ROM_QSTR( MP_QSTR_slider ), MP_ROM_PTR( &Mu_slider_obj) },
    { MP_ROM_QSTR( MP_QSTR_number ), MP_ROM_PTR( &Mu_number_obj) },
    { MP_ROM_QSTR( MP_QSTR_header ), MP_ROM_PTR( &Mu_header_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_treenode ), MP_ROM_PTR( &Mu_begin_treenode_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_window ), MP_ROM_PTR( &Mu_begin_window_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_panel ), MP_ROM_PTR( &Mu_begin_panel_obj) },
    { MP_ROM_QSTR( MP_QSTR_text ), MP_ROM_PTR( &Mu_text_obj) },
    { MP_ROM_QSTR( MP_QSTR_label ), MP_ROM_PTR( &Mu_label_obj) },
    { MP_ROM_QSTR( MP_QSTR_button_ex ), MP_ROM_PTR( &Mu_button_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_checkbox ), MP_ROM_PTR( &Mu_checkbox_obj) },
    { MP_ROM_QSTR( MP_QSTR_textbox_raw ), MP_ROM_PTR( &Mu_textbox_raw_obj) },
    { MP_ROM_QSTR( MP_QSTR_textbox_ex ), MP_ROM_PTR( &Mu_textbox_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_slider_ex ), MP_ROM_PTR( &Mu_slider_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_number_ex ), MP_ROM_PTR( &Mu_number_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_header_ex ), MP_ROM_PTR( &Mu_header_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_treenode_ex ), MP_ROM_PTR( &Mu_begin_treenode_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_end_treenode ), MP_ROM_PTR( &Mu_end_treenode_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_window_ex ), MP_ROM_PTR( &Mu_begin_window_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_end_window ), MP_ROM_PTR( &Mu_end_window_obj) },
    { MP_ROM_QSTR( MP_QSTR_open_popup ), MP_ROM_PTR( &Mu_open_popup_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_popup ), MP_ROM_PTR( &Mu_begin_popup_obj) },
    { MP_ROM_QSTR( MP_QSTR_end_popup ), MP_ROM_PTR( &Mu_end_popup_obj) },
    { MP_ROM_QSTR( MP_QSTR_begin_panel_ex ), MP_ROM_PTR( &Mu_begin_panel_ex_obj) },
    { MP_ROM_QSTR( MP_QSTR_end_panel ), MP_ROM_PTR( &Mu_end_panel_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw ), MP_ROM_PTR( &Mu_draw_obj) },
    //{ MP_ROM_QSTR( MP_QSTR_draw_line_fast ), MP_ROM_PTR( &Mu_draw_line_fast_obj) },
    { MP_ROM_QSTR( MP_QSTR_draw_line_fast_fb ), MP_ROM_PTR( &Mu_draw_line_fast_fb_obj) },
    { MP_ROM_QSTR( MP_QSTR_set_style ), MP_ROM_PTR( &Mu_set_style_obj) },
    
    
    { MP_ROM_QSTR(MP_QSTR_COLOR_TEXT), MP_ROM_INT(MU_COLOR_TEXT) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BORDER), MP_ROM_INT(MU_COLOR_BORDER) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_WINDOWBG), MP_ROM_INT(MU_COLOR_WINDOWBG) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_TITLEBG), MP_ROM_INT(MU_COLOR_TITLEBG) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_TITLETEXT), MP_ROM_INT(MU_COLOR_TITLETEXT) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_PANELBG), MP_ROM_INT(MU_COLOR_PANELBG) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BUTTON), MP_ROM_INT(MU_COLOR_BUTTON) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BUTTONHOVER), MP_ROM_INT(MU_COLOR_BUTTONHOVER) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BUTTONFOCUS), MP_ROM_INT(MU_COLOR_BUTTONFOCUS) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BASE), MP_ROM_INT(MU_COLOR_BASE) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BASEHOVER), MP_ROM_INT(MU_COLOR_BASEHOVER) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_BASEFOCUS), MP_ROM_INT(MU_COLOR_BASEFOCUS) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_SCROLLBASE), MP_ROM_INT(MU_COLOR_SCROLLBASE) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_SCROLLTHUMB), MP_ROM_INT(MU_COLOR_SCROLLTHUMB) },
    { MP_ROM_QSTR(MP_QSTR_COLOR_MAX), MP_ROM_INT(MU_COLOR_MAX) },

    { MP_ROM_QSTR(MP_QSTR_ICON_CLOSE), MP_ROM_INT(MU_ICON_CLOSE) },
    { MP_ROM_QSTR(MP_QSTR_ICON_CHECK), MP_ROM_INT(MU_ICON_CHECK) },
    { MP_ROM_QSTR(MP_QSTR_ICON_COLLAPSED), MP_ROM_INT(MU_ICON_COLLAPSED) },
    { MP_ROM_QSTR(MP_QSTR_ICON_EXPANDED), MP_ROM_INT(MU_ICON_EXPANDED) },
    { MP_ROM_QSTR(MP_QSTR_ICON_MAX), MP_ROM_INT(MU_ICON_MAX) },

    { MP_ROM_QSTR(MP_QSTR_OPT_ALIGNCENTER), MP_ROM_INT(MU_OPT_ALIGNCENTER) },
    { MP_ROM_QSTR(MP_QSTR_OPT_ALIGNRIGHT), MP_ROM_INT(MU_OPT_ALIGNRIGHT) },
    { MP_ROM_QSTR(MP_QSTR_OPT_NOINTERACT), MP_ROM_INT(MU_OPT_NOINTERACT) },
    { MP_ROM_QSTR(MP_QSTR_OPT_NOFRAME), MP_ROM_INT(MU_OPT_NOFRAME) },
    { MP_ROM_QSTR(MP_QSTR_OPT_NORESIZE), MP_ROM_INT(MU_OPT_NORESIZE) },
    { MP_ROM_QSTR(MP_QSTR_OPT_NOSCROLL), MP_ROM_INT(MU_OPT_NOSCROLL) },
    { MP_ROM_QSTR(MP_QSTR_OPT_NOCLOSE), MP_ROM_INT(MU_OPT_NOCLOSE) },
    { MP_ROM_QSTR(MP_QSTR_OPT_NOTITLE), MP_ROM_INT(MU_OPT_NOTITLE) },
    { MP_ROM_QSTR(MP_QSTR_OPT_HOLDFOCUS), MP_ROM_INT(MU_OPT_HOLDFOCUS) },
    { MP_ROM_QSTR(MP_QSTR_OPT_AUTOSIZE), MP_ROM_INT(MU_OPT_AUTOSIZE) },
    { MP_ROM_QSTR(MP_QSTR_OPT_POPUP), MP_ROM_INT(MU_OPT_POPUP) },
    { MP_ROM_QSTR(MP_QSTR_OPT_CLOSED), MP_ROM_INT(MU_OPT_CLOSED) },
    { MP_ROM_QSTR(MP_QSTR_OPT_EXPANDED), MP_ROM_INT(MU_OPT_EXPANDED) },

    { MP_ROM_QSTR(MP_QSTR_MOUSE_LEFT), MP_ROM_INT(MU_MOUSE_LEFT) },
    { MP_ROM_QSTR(MP_QSTR_MOUSE_RIGHT), MP_ROM_INT(MU_MOUSE_RIGHT) },
    { MP_ROM_QSTR(MP_QSTR_MOUSE_MIDDLE), MP_ROM_INT(MU_MOUSE_MIDDLE) },

    { MP_ROM_QSTR(MP_QSTR_KEY_SHIFT), MP_ROM_INT(MU_KEY_SHIFT) },
    { MP_ROM_QSTR(MP_QSTR_KEY_CTRL), MP_ROM_INT(MU_KEY_CTRL) },
    { MP_ROM_QSTR(MP_QSTR_KEY_ALT), MP_ROM_INT(MU_KEY_ALT) },
    { MP_ROM_QSTR(MP_QSTR_KEY_BACKSPACE), MP_ROM_INT(MU_KEY_BACKSPACE) },
    { MP_ROM_QSTR(MP_QSTR_KEY_RETURN), MP_ROM_INT(MU_KEY_RETURN) },
    
};

/*
MP_DEFINE_CONST_OBJ_TYPE(
    microui_type,
    MP_QSTR_microui,
    MP_TYPE_FLAG_NONE,
    make_new, microui_make_new,
    print, microui_print,
    locals_dict, &microui_locals_dict
);*/

const mp_obj_type_t microui_type = 
{
    { &mp_type_type },
    .name = MP_QSTR_microui,
    .make_new = microui_make_new,
    .print = microui_print,
    .locals_dict = (mp_obj_dict_t*)&microui_locals_dict,
};

const mp_map_elem_t microui_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR( MP_QSTR___name__ ), MP_OBJ_NEW_QSTR( MP_QSTR_microui ) },
    { MP_OBJ_NEW_QSTR( MP_QSTR_microui ), (mp_obj_t)&microui_type },
};
const mp_obj_module_t microui_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&microui_globals,
};

/****************************************************************************
 * Public Variables Definitions.
 ****************************************************************************/
static MP_DEFINE_CONST_DICT( microui_locals_dict, microui_locals_dict_table );
static MP_DEFINE_CONST_DICT( microui_globals, microui_globals_table );

/****************************************************************************
 * Private Functions Definitions.
 ****************************************************************************/

static int text_width(mu_Font font, const char *text, int len) {
  //if (len == -1) { len = strlen(text); }
  //return 8*len;
    int i = 0;
    int l = 0;
    if( len == -1 )
    {
        for( i = 0 ; text[i] != '#' && text[i] != '\0' ; i++ )
        {
            l += 1;
        }
    }
    else
    {
        for( i = 0 ; i < len && text[i] != '#' && text[i] != '\0' ; i++ )
        {
            l += 1;
        }
    }
    return l*8;
}

static int text_height(mu_Font font) {
  return 8;
}


static mp_obj_t microui_make_new( const mp_obj_type_t *type_in, size_t n_args, size_t n_kw, const mp_obj_t *args )
{
    mp_arg_check_num( n_args, n_kw, 0, 0, false );
    tMicroui *self = m_new_obj( tMicroui );
    self->base.type = &microui_type;
    mu_Context* ctx = &self->ctx;
    // zero with memset
    memset( ctx, 0, sizeof(mu_Context) );
    
    mu_init(ctx);
    ctx->text_width = text_width;
    ctx->text_height = text_height;
  
    return MP_OBJ_FROM_PTR( self );
}

static void microui_print( const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind )
{
    (void)kind;
    tMicroui *self = MP_OBJ_TO_PTR( self_in );
    mp_printf( print, "microui=%x\n", (int)self );
}


#include <stdint.h>
/*
#include "stm32g474xx.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_spi.h"

#define CS_PORT GPIOB
#define CS_PIN  LL_GPIO_PIN_6
#define DC_PORT GPIOA
#define DC_PIN  LL_GPIO_PIN_8

void write_reg( uint8_t reg, uint8_t *buf, uint8_t len )
{
    //LL_GPIO_ResetOutputPin( CS_PORT, CS_PIN );
    LL_GPIO_ResetOutputPin( DC_PORT, DC_PIN );
    
    LL_SPI_TransmitData8( SPI1, reg );
    while( !LL_SPI_IsActiveFlag_TXE( SPI1 ) );
    while( LL_SPI_IsActiveFlag_BSY( SPI1 ) );
    
    LL_GPIO_SetOutputPin( DC_PORT, DC_PIN );
    while( len-- )
    {
        LL_SPI_TransmitData8( SPI1, *buf++ );
        while( !LL_SPI_IsActiveFlag_TXE( SPI1 ) );
    }
    while( LL_SPI_IsActiveFlag_BSY( SPI1 ) );
    //LL_GPIO_SetOutputPin( CS_PORT, CS_PIN );
}
*/
/*
def set_pixel( self, x, y, color ):
    w = 1
    h = 1
    x0 = x
    y0 = y
    x1 = x0 + w - 1
    y1 = y0 + h - 1
    self.buf2[0] = x0 >> 8
    self.buf2[1] = x0 &  0xff
    self.write_register( St7789.CASET, self.buf2 )
    self.buf2[0] = y0 >> 8
    self.buf2[1] = y0 &  0xff
    self.write_register( St7789.RASET, self.buf2 )        
    self.buf2[0] = color >> 8
    self.buf2[1] = color &  0xff
    self.write_register( St7789.RAMWR, self.buf2 )
*/
/*
void set_pixel( uint16_t x, uint16_t y, uint16_t color )
{
    uint8_t buf[2];
    buf[0] = x >> 8;
    buf[1] = x & 0xff;
    write_reg( 0x2a, buf, 2 );
    buf[0] = y >> 8;
    buf[1] = y & 0xff;
    write_reg( 0x2b, buf, 2 );
    buf[0] = color >> 8;
    buf[1] = color & 0xff;
    write_reg( 0x2c, buf, 2 );
}
*/
/*
mu.draw_line_fast( data, color )
*/
/*
static mp_obj_t Mu_draw_line_fast(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    
    // values = array.array("h", [...])
    // ctx.draw_line_fast( reg, values )
    // get the pointer to array data.
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise( args_in[1], &bufinfo, MP_BUFFER_READ );
    uint16_t color = mp_obj_get_int(args_in[2]);
    
    //draw_line_fast( reg, bufinfo.buf, bufinfo.len );
    LL_GPIO_ResetOutputPin( CS_PORT, CS_PIN );
    for( int i = 0 ; i < bufinfo.len/2 ; i++ )
    {
        int16_t v = ((int16_t*)bufinfo.buf)[i];
        set_pixel( i, v, color );
    }
    LL_GPIO_SetOutputPin( CS_PORT, CS_PIN );
    
    return mp_const_none;
}
*/


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

uint8_t rgba_to_111( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
    uint8_t color = 0;
    if( r ) color |= 0x1;
    if( g ) color |= 0x2;
    if( b ) color |= 0x4;
    return color;
}
typedef struct _mp_obj_framebuf_t mp_obj_framebuf_t;
extern mp_obj_t framebuf_pixel(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_rect(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_fill_rect(size_t n_args, const mp_obj_t *args);
extern mp_obj_t framebuf_text(size_t n_args, const mp_obj_t *args);

static mp_obj_t Mu_draw_line_fast_fb(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 6, 6, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    
    // values = array.array("h", [...])
    // ctx.draw_line_fast( reg, values )
    // get the pointer to array data.
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise( args_in[1], &bufinfo, MP_BUFFER_READ );
    uint16_t color = mp_obj_get_int(args_in[2]);
    uint16_t colot_tmp = color;
    color = ( (color & 0xff) << 8 ) | ( (color & 0xff00) >> 8 );

    int x0 = -mp_obj_get_int( args_in[3] );
    int y0 = -mp_obj_get_int( args_in[4] );
    mp_obj_framebuf_t *fb_in = MP_OBJ_TO_PTR( args_in[5] );
    
    int i;
    int16_t *values = (int16_t*)bufinfo.buf;
    int len = bufinfo.len/2;
    for( i = -x0 ; i < len ; i++ )
    {
        int16_t v = values[i];
        int x = i;
        int y = v;
        framebuf_pixel( 
            4, 
            (mp_obj_t[4])
            { 
                fb_in, 
                mp_obj_new_int(x0+x), 
                mp_obj_new_int(y0+y), 
                mp_obj_new_int(color)
            } 
        );
    }
    
    return mp_const_none;
}

static mp_obj_t Mu_draw(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    
    int x0 = -mp_obj_get_int( args_in[1] );
    int y0 = -mp_obj_get_int( args_in[2] );
    mp_obj_framebuf_t *fb_in = MP_OBJ_TO_PTR( args_in[3] );
    
    mu_Command *cmd = NULL;
    while (mu_next_command(ctx, &cmd)) {
      switch (cmd->type) {
        case MU_COMMAND_RECT: //r_draw_rect(cmd->rect.rect, cmd->rect.color); break;
            framebuf_fill_rect(6,
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+cmd->rect.rect.x),
                    mp_obj_new_int(y0+cmd->rect.rect.y),
                    mp_obj_new_int(cmd->rect.rect.w),
                    mp_obj_new_int(cmd->rect.rect.h),
                    mp_obj_new_int(rgba_to_111(
                        cmd->rect.color.r, 
                        cmd->rect.color.g, 
                        cmd->rect.color.b, 
                        cmd->rect.color.a)
                    )
                }
            );
            break;
        case MU_COMMAND_BOX: //r_draw_rect(cmd->rect.rect, cmd->rect.color); break;
            framebuf_rect(6,
                (mp_obj_t[6]){
                    fb_in, 
                    mp_obj_new_int(x0+cmd->box.rect.x),
                    mp_obj_new_int(y0+cmd->box.rect.y),
                    mp_obj_new_int(cmd->box.rect.w),
                    mp_obj_new_int(cmd->box.rect.h),
                    mp_obj_new_int(rgba_to_111(
                        cmd->box.color.r, 
                        cmd->box.color.g, 
                        cmd->box.color.b, 
                        cmd->box.color.a)
                    )
                }
            );
            break;
        case MU_COMMAND_TEXT: //r_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color); break;
            framebuf_text(
                5, 
                (mp_obj_t[5]){
                    fb_in, 
                    mp_obj_new_str(cmd->text.str, strlen(cmd->text.str) ), 
                    mp_obj_new_int(x0+cmd->text.pos.x), 
                    mp_obj_new_int(y0+cmd->text.pos.y), 
                    mp_obj_new_int(rgba_to_111(
                        cmd->text.color.r, 
                        cmd->text.color.g, 
                        cmd->text.color.b, 
                        cmd->text.color.a)
                    )
                }
            );
            break;
        case MU_COMMAND_ICON: //r_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
        {
            /*
            enum {
              MU_ICON_CLOSE = 1,
              MU_ICON_CHECK,
              MU_ICON_COLLAPSED,
              MU_ICON_EXPANDED,
              MU_ICON_MAX
            };*/
            uint8_t icon_map[MU_ICON_MAX] = {
                ' ',
                133,
                132,
                129,//'>',
                130,//'V',
            };
            framebuf_text(
                5, 
                (mp_obj_t[5]){
                    fb_in, 
                    mp_obj_new_str(&icon_map[cmd->icon.id], 1 ), 
                    mp_obj_new_int(x0+cmd->icon.rect.x+8), 
                    mp_obj_new_int(y0+cmd->icon.rect.y+6), 
                    mp_obj_new_int(rgba_to_111(
                        cmd->icon.color.r, 
                        cmd->icon.color.g, 
                        cmd->icon.color.b, 
                        cmd->icon.color.a)
                    )
                }
            );
            break;
        }
        case MU_COMMAND_CLIP: //r_set_clip_rect(cmd->clip.rect); break;
            break;
        default:
            break;
      }
    }
}

static mp_obj_t Mu_vec2(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_vec2\n " );
    return mp_const_none;
}

static mp_obj_t Mu_rect(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_rect\n " );
    return mp_const_none;
}

static mp_obj_t Mu_color(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_color\n " );
    return mp_const_none;
}

static mp_obj_t Mu_init(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_init(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_begin(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_begin(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_end(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_end(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_set_focus(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_set_focus\n " );
    return mp_const_none;
}

static mp_obj_t Mu_get_id(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_get_id\n " );
    return mp_const_none;
}

static mp_obj_t Mu_push_id(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    void* data = (void*) mp_obj_get_int( args_in[1] );
    int size = mp_obj_get_int( args_in[2] );
    mu_push_id(ctx, data, size);
    return mp_const_none;
}

static mp_obj_t Mu_pop_id(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_pop_id(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_push_clip_rect(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect rect = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    mu_push_clip_rect(ctx, rect);
    return mp_const_none;
}

static mp_obj_t Mu_pop_clip_rect(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_pop_clip_rect(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_get_clip_rect(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_get_clip_rect\n " );
    return mp_const_none;
}

static mp_obj_t Mu_check_clip(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect r = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    int retval = mu_check_clip(ctx, r);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_get_current_container(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_get_current_container\n " );
    return mp_const_none;
}

static mp_obj_t Mu_get_container(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_get_container\n " );
    return mp_const_none;
}

static mp_obj_t Mu_bring_to_front(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_Container* cnt = (mu_Container*) mp_obj_get_int( args_in[1] );
    mu_bring_to_front(ctx, cnt);
    return mp_const_none;
}

static mp_obj_t Mu_pool_init(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_pool_init\n " );
    return mp_const_none;
}

static mp_obj_t Mu_pool_get(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_pool_get\n " );
    return mp_const_none;
}

static mp_obj_t Mu_pool_update(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_PoolItem* items = (mu_PoolItem*) mp_obj_get_int( args_in[1] );
    int idx = mp_obj_get_int( args_in[2] );
    mu_pool_update(ctx, items, idx);
    return mp_const_none;
}

static mp_obj_t Mu_input_mousemove(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int x = mp_obj_get_int( args_in[1] );
    int y = mp_obj_get_int( args_in[2] );
    mu_input_mousemove(ctx, x, y);
    return mp_const_none;
}

static mp_obj_t Mu_input_mousedown(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int x = mp_obj_get_int( args_in[1] );
    int y = mp_obj_get_int( args_in[2] );
    int btn = mp_obj_get_int( args_in[3] );
    mu_input_mousedown(ctx, x, y, btn);
    return mp_const_none;
}

static mp_obj_t Mu_input_mouseup(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int x = mp_obj_get_int( args_in[1] );
    int y = mp_obj_get_int( args_in[2] );
    int btn = mp_obj_get_int( args_in[3] );
    mu_input_mouseup(ctx, x, y, btn);
    return mp_const_none;
}

static mp_obj_t Mu_input_scroll(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int x = mp_obj_get_int( args_in[1] );
    int y = mp_obj_get_int( args_in[2] );
    mu_input_scroll(ctx, x, y);
    return mp_const_none;
}

static mp_obj_t Mu_input_keydown(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int key = mp_obj_get_int( args_in[1] );
    mu_input_keydown(ctx, key);
    return mp_const_none;
}

static mp_obj_t Mu_input_keyup(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int key = mp_obj_get_int( args_in[1] );
    mu_input_keyup(ctx, key);
    return mp_const_none;
}

static mp_obj_t Mu_input_text(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*text = mp_obj_str_get_str( args_in[1] );
    mu_input_text(ctx, text);
    return mp_const_none;
}

static mp_obj_t Mu_push_command(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_push_command\n " );
    return mp_const_none;
}

static mp_obj_t Mu_next_command(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_next_command\n " );
    return mp_const_none;
}

static mp_obj_t Mu_set_clip(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect rect = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    mu_set_clip(ctx, rect);
    return mp_const_none;
}

static mp_obj_t Mu_draw_rect(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect rect = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    mu_Color color = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    mu_draw_rect(ctx, rect, color);
    return mp_const_none;
}

static mp_obj_t Mu_draw_box(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect rect = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    mu_Color color = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    mu_draw_box(ctx, rect, color);
    return mp_const_none;
}

static mp_obj_t Mu_draw_text(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_draw_text\n " );
    return mp_const_none;
}

static mp_obj_t Mu_draw_icon(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int id = mp_obj_get_int( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    mu_Rect rect = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    mp_obj_t *arg_3 = NULL;
    size_t arg_3_len = 0;
    mp_obj_get_array(args_in[3], &arg_3_len, &arg_3);
    mu_Color color = {
        mp_obj_get_int(arg_3[0]),
        mp_obj_get_int(arg_3[1]),
        mp_obj_get_int(arg_3[2]),
        mp_obj_get_int(arg_3[3])
    };
    mu_draw_icon(ctx, id, rect, color);
    return mp_const_none;
}

static mp_obj_t Mu_layout_row(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    
    //int items = mp_obj_get_int( args_in[1] );
    //int* widths = (int*) mp_obj_get_int( args_in[2] );
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    int items = arg_1_len;
    if( items > 8 )
    {
        printf( "warning, items > 8\n" );
        items = 8;
    }
    int widths[8];
    for( int i = 0 ; i < items ; i++ )
    {
        widths[i] = mp_obj_get_int(arg_1[i]);
    }
    
    int height = mp_obj_get_int( args_in[2] );
    mu_layout_row(ctx, items, widths, height);
    return mp_const_none;
}

static mp_obj_t Mu_layout_width(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int width = mp_obj_get_int( args_in[1] );
    mu_layout_width(ctx, width);
    return mp_const_none;
}

static mp_obj_t Mu_layout_height(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    int height = mp_obj_get_int( args_in[1] );
    mu_layout_height(ctx, height);
    return mp_const_none;
}

static mp_obj_t Mu_layout_begin_column(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_layout_begin_column(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_layout_end_column(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_layout_end_column(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_layout_set_next(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect r = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    int relative = mp_obj_get_int( args_in[2] );
    mu_layout_set_next(ctx, r, relative);
    return mp_const_none;
}

static mp_obj_t Mu_layout_next(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_Rect rect = mu_layout_next( ctx );
    mp_obj_t tuple[] = {
        mp_obj_new_int( rect.x ),
        mp_obj_new_int( rect.y ),
        mp_obj_new_int( rect.w ),
        mp_obj_new_int( rect.h ),
    };
    return mp_obj_new_tuple( 4, tuple );
}

static mp_obj_t Mu_draw_control_frame(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_draw_control_frame\n " );
    return mp_const_none;
}

static mp_obj_t Mu_draw_control_text(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*str = mp_obj_str_get_str( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    mu_Rect rect = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    int colorid = mp_obj_get_int( args_in[3] );
    int opt = mp_obj_get_int( args_in[4] );
    mu_draw_control_text(ctx, str, rect, colorid, opt);
    return mp_const_none;
}

static mp_obj_t Mu_mouse_over(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mp_obj_t *arg_1 = NULL;
    size_t arg_1_len = 0;
    mp_obj_get_array(args_in[1], &arg_1_len, &arg_1);
    mu_Rect rect = {
        mp_obj_get_int(arg_1[0]),
        mp_obj_get_int(arg_1[1]),
        mp_obj_get_int(arg_1[2]),
        mp_obj_get_int(arg_1[3])
    };
    int retval = mu_mouse_over(ctx, rect);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_update_control(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_update_control\n " );
    return mp_const_none;
}

static mp_obj_t Mu_button(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int retval = mu_button(ctx, label);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_textbox(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*buf = mp_obj_str_get_str( args_in[1] );
    int bufsz = mp_obj_get_int( args_in[2] );
    int retval = mu_textbox(ctx, buf, bufsz);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_slider(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    
    char*label = mp_obj_str_get_str( args_in[1] );
    
    mu_Real value = mp_obj_get_float( args_in[2] );
    mu_Real low = mp_obj_get_float( args_in[3] );
    mu_Real high = mp_obj_get_float( args_in[4] );
    int retval = mu_slider(ctx, label, &value, low, high);
    mp_obj_t tuple[] = {
        mp_obj_new_int( retval ),
        mp_obj_new_float( value ),
    };
    return mp_obj_new_tuple( 2, tuple );
}

static mp_obj_t Mu_number(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_Real value = mp_obj_get_float( args_in[1] );
    mu_Real step = mp_obj_get_float( args_in[2] );
    int retval = mu_number(ctx, &value, step);
    mp_obj_t tuple[] = {
        mp_obj_new_int( retval ),
        mp_obj_new_float( value ),
    };
    return mp_obj_new_tuple( 2, tuple );
}

static mp_obj_t Mu_header(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int retval = mu_header(ctx, label);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_begin_treenode(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int retval = mu_begin_treenode(ctx, label);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_begin_window(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*title = mp_obj_str_get_str( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    mu_Rect rect = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    int retval = mu_begin_window(ctx, title, rect);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_begin_panel(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    mu_begin_panel(ctx, name);
    return mp_const_none;
}

static mp_obj_t Mu_text(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    const char*text = mp_obj_str_get_str( args_in[1] );
    mu_text(ctx, text);
    return mp_const_none;
}

static mp_obj_t Mu_label(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*text = mp_obj_str_get_str( args_in[1] );
    mu_label(ctx, text);
    return mp_const_none;
}

static mp_obj_t Mu_button_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int icon = mp_obj_get_int( args_in[2] );
    int opt = mp_obj_get_int( args_in[3] );
    int retval = mu_button_ex(ctx, label, icon, opt);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_checkbox(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int state = mp_obj_get_int( args_in[2] );
    int retval = mu_checkbox(ctx, label, &state);
    mp_obj_t tuple[] = {
        mp_obj_new_int( retval ),
        mp_obj_new_int( state ),
    };
    return mp_obj_new_tuple( 2, tuple );
    
}

static mp_obj_t Mu_textbox_raw(size_t n_args, const mp_obj_t *args_in)
{
    printf( "Not implemented: mu_textbox_raw\n " );
    return mp_const_none;
}

static mp_obj_t Mu_textbox_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*buf = mp_obj_str_get_str( args_in[1] );
    int bufsz = mp_obj_get_int( args_in[2] );
    int opt = mp_obj_get_int( args_in[3] );
    int retval = mu_textbox_ex(ctx, buf, bufsz, opt);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_slider_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 8, 8, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    
    mu_Real value = mp_obj_get_float( args_in[2] );
    mu_Real low = mp_obj_get_float( args_in[3] );
    mu_Real high = mp_obj_get_float( args_in[4] );
    mu_Real step = mp_obj_get_float( args_in[5] );
    char*fmt = mp_obj_str_get_str( args_in[6] );
    int opt = mp_obj_get_int( args_in[7] );
    int retval = mu_slider_ex(ctx, label, &value, low, high, step, fmt, opt);
    mp_obj_t tuple[] = {
        mp_obj_new_int( retval ),
        mp_obj_new_float( value ),
    };
    return mp_obj_new_tuple( 2, tuple );
}

static mp_obj_t Mu_number_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 5, 5, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_Real value = mp_obj_get_float( args_in[1] );
    mu_Real step = mp_obj_get_float( args_in[2] );
    char*fmt = mp_obj_str_get_str( args_in[3] );
    int opt = mp_obj_get_int( args_in[4] );
    int retval = mu_number_ex(ctx, &value, step, fmt, opt);
    mp_obj_t tuple[] = {
        mp_obj_new_int( retval ),
        mp_obj_new_float( value ),
    };
    return mp_obj_new_tuple( 2, tuple );
}

static mp_obj_t Mu_header_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int opt = mp_obj_get_int( args_in[2] );
    int retval = mu_header_ex(ctx, label, opt);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_begin_treenode_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*label = mp_obj_str_get_str( args_in[1] );
    int opt = mp_obj_get_int( args_in[2] );
    int retval = mu_begin_treenode_ex(ctx, label, opt);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_end_treenode(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_end_treenode(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_begin_window_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 4, 4, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*title = mp_obj_str_get_str( args_in[1] );
    mp_obj_t *arg_2 = NULL;
    size_t arg_2_len = 0;
    mp_obj_get_array(args_in[2], &arg_2_len, &arg_2);
    mu_Rect rect = {
        mp_obj_get_int(arg_2[0]),
        mp_obj_get_int(arg_2[1]),
        mp_obj_get_int(arg_2[2]),
        mp_obj_get_int(arg_2[3])
    };
    int opt = mp_obj_get_int( args_in[3] );
    int retval = mu_begin_window_ex(ctx, title, rect, opt);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_end_window(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_end_window(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_open_popup(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    mu_open_popup(ctx, name);
    return mp_const_none;
}

static mp_obj_t Mu_begin_popup(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    int retval = mu_begin_popup(ctx, name);
    return mp_obj_new_int( retval );
}

static mp_obj_t Mu_end_popup(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_end_popup(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_begin_panel_ex(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 3, 3, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    char*name = mp_obj_str_get_str( args_in[1] );
    int opt = mp_obj_get_int( args_in[2] );
    mu_begin_panel_ex(ctx, name, opt);
    return mp_const_none;
}

static mp_obj_t Mu_end_panel(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 1, 1, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Context* ctx = &self->ctx;
    mu_end_panel(ctx);
    return mp_const_none;
}

static mp_obj_t Mu_set_style(size_t n_args, const mp_obj_t *args_in)
{
    mp_arg_check_num(n_args, 0, 2, 2, false);
    tMicroui *self = MP_OBJ_TO_PTR( args_in[0] );
    mu_Style *style = MP_OBJ_TO_PTR( args_in[1] );
    mu_set_style(&self->ctx, style);
    return mp_const_none;
}

/****************************************************************************
 * Public Functions Definitions.
 ****************************************************************************/

