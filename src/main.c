

int entry(int argc, char **argv)
{
	window.title = STR("Simple Tower Defense");
    window.scaled_width  = 1280;
    window.scaled_height = 720;
    window.x = 200;
    window.y = 200;
    window.clear_color = hex_to_rgba(0x181818ff);
    os_update(); // Update window asap when starting the game

    Gfx_Image *player_sprite = load_image_from_disk(STR("oogabooga/examples/hammer.png"), get_heap_allocator());
    assert(player_sprite, "Failed loading hammer.png");

    Gfx_Font *font = load_font_from_disk(STR("C:/windows/fonts/arial.ttf"), get_heap_allocator());
    assert(font, "Failed loading arial.ttf, %d", GetLastError());

    render_atlas_if_not_yet_rendered(font, 32, 'A');

    seed_for_random = rdtsc();

    const float64 fps_limit = 69000;
    const float64 min_frametime = 1.0 / fps_limit;

    float64 last_time = os_get_current_time_in_seconds();
    while (!window.should_close) tm_scope("Frame") {
        reset_temporary_storage();

        float64 now = os_get_current_time_in_seconds();
        float64 delta = now - last_time;
        if (delta < min_frametime) {
            os_high_precision_sleep((min_frametime-delta)*1000.0);
            now = os_get_current_time_in_seconds();
            delta = now - last_time;
        }
        last_time = now;
        tm_scope("os_update") {
            os_update();
        }

        if (is_key_just_released(KEY_ESCAPE)) {
            window.should_close = true;
        }

        // const float32 cam_move_speed = 4.0;
        // Vector2 cam_move_axis = v2(0, 0);
        // if (is_key_down('A')) {
        //     cam_move_axis.x -= 1.0;
        // }
        // if (is_key_down('D')) {
        //     cam_move_axis.x += 1.0;
        // }
        // if (is_key_down('S')) {
        //     cam_move_axis.y -= 1.0;
        // }
        // if (is_key_down('W')) {
        //     cam_move_axis.y += 1.0;
        // }

        // Vector2 cam_move = v2_mulf(cam_move_axis, delta * cam_move_speed);
        // camera_view = m4_translate(camera_view, v3(v2_expand(cam_move), 0));
        // draw_frame.view = camera_view;

        // local_persist bool do_enable_z_sorting = false;
        // draw_frame.enable_z_sorting = do_enable_z_sorting;
        // if (is_key_just_pressed('Z')) do_enable_z_sorting = !do_enable_z_sorting;

        // if (do_enable_z_sorting) {
        //     push_window_scissor(
        //         v2(input_frame.mouse_x-256, input_frame.mouse_y-256),
        //         v2(input_frame.mouse_x+256, input_frame.mouse_y+256)
        //     );
        // }

        // seed_for_random = 69;
        // for (u64 i = 0; i < 30000; i++) {
        //     float32 aspect = (float32)window.width/(float32)window.height;
        //     float min_x = -aspect;
        //     float max_x = aspect;
        //     float min_y = -1;
        //     float max_y = 1;

        //     float x = get_random_float32() * (max_x-min_x) + min_x;
        //     float y = get_random_float32() * (max_y-min_y) + min_y;

        //     push_z_layer((s32)(y*100));
        //     draw_image(bush_image, v2(x, y), v2(0.1, 0.1), COLOR_WHITE);
        //     pop_z_layer();
        // }
        // seed_for_random = rdtsc();

        // Matrix4 hammer_xform = m4_scalar(1.0);
        // hammer_xform         = m4_rotate_z(hammer_xform, (f32)now);
        // hammer_xform         = m4_translate(hammer_xform, v3(-.25f, -.25f, 0));
        // push_z_layer(1000001);
        // draw_image_xform(hammer_image, hammer_xform, v2(.5f, .5f), COLOR_RED);
        // draw_image_xform(hammer_image, hammer_xform, v2(.25f, .25f), COLOR_GREEN);
        // pop_z_layer();

        // Vector2 hover_position = v2_rotate_point_around_pivot(v2(-.5, -.5), v2(0, 0), (f32)now);
        // Vector2 local_pivot = v2(.125f, .125f);
        // draw_circle(v2_sub(hover_position, local_pivot), v2(.25f, .25f), v4((sin(now)+1.0)/2.0, 1.0, 0.0, 1.0));

        // draw_image(bush_image, v2(0.65, 0.65), v2(0.2*sin(now), 0.2*sin(now)), COLOR_WHITE);

        // u32 atlas_index = 0;
        // Gfx_Font_Atlas *atlas = (Gfx_Font_Atlas*)hash_table_find(&font->variations[32].atlases, atlas_index);

        // draw_text(font, STR("I am text"), 128, v2(sin(now), -0.61), v2(0.001, 0.001), COLOR_BLACK);
        // draw_text(font, STR("I am text"), 128, v2(sin(now)-0.01, -0.6), v2(0.001, 0.001), COLOR_WHITE);

        // draw_text(font, STR("Hello jje\nnew line"), 128, v2(-1, 0.5), v2(0.001, 0.001), COLOR_WHITE);

        // local_persist bool show = false;
        // if (is_key_just_pressed('T')) show = !show;

        // if (show) draw_image(atlas->image, v2(-1.6, -1), v2(4, 4), COLOR_WHITE);

        // if (do_enable_z_sorting) {
        //     pop_window_scissor();
        // }

        tm_scope("gfx_update") {
            gfx_update();
        }

        if (is_key_just_released('E')) {
            log("FPS: %.2f", 1.0 / delta);
            log("ms: %.2f", delta*1000.0);
        }
    }

    return 0;
}