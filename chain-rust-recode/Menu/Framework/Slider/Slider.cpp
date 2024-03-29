#include <algorithm>
#include "../gui.h"
#include "../../../stdafx.hpp"

bool GUI::Controls::Slider( const std::string& name, float* var_name, float min, float max, const std::string& display, float increment ) {
	Vector2 CursorPos = PopCursorPos( );
	Vector2 DrawPos = ctx->pos + CursorPos;
	Vector2 DrawSize( std::min( ( int )ctx->ParentSize.x - 90, 270 ), 6 );

	DrawPos.x += 20;

	Render::DirectX::Fonts::menu.draw_text( GUI::SplitStr( name, '#' )[ 0 ].data( ), DrawPos + Vector2( 0, -3 ), Color( 203, 203, 203 ), 4 );

	DrawPos.y += 11;

	bool hovered = InputHelper::IsHoveringOverPoint( DrawPos, DrawSize + Vector2( 0, 1 ) ) && InputHelper::IsHoveringOverPoint( ctx->ParentPos, ctx->ParentSize );

	if( hovered && ctx->FocusedID != GUI::Hash( name ) )
		Render::DirectX::gradient_v( DrawPos + 1, DrawSize - 1, { 57, 57, 57 }, { 73, 73, 73 } );
	else
		Render::DirectX::gradient_v( DrawPos + 1, DrawSize - 1, { 52, 52, 52 }, { 68, 68, 68 } );

	float width = GUI::MapNumber( *var_name, min, max, 0, DrawSize.x );
	Render::DirectX::gradient_v( DrawPos + 1, Vector2( width + 1, DrawSize.y ) - 1, g_Vars.menu.menu_color.ToRegularColor( ), g_Vars.menu.menu_color.ToRegularColor( ) * 0.75f );

	Render::DirectX::rect( DrawPos, DrawSize, { 10, 10, 10 } );

	char buf[ 32 ];
	sprintf_s( buf, display.c_str( ), *var_name );

	Vector2 tooltip_size = Render::DirectX::Fonts::menu_bold.measure_size( buf );
	Render::DirectX::Fonts::menu_bold.draw_text( buf, DrawPos + Vector2( width - ( tooltip_size.x / 2 ), DrawSize.y - 6 ), Color( 203, 203, 203 ), 8 );

	if( ctx->FocusedID == 0 ) {
		if( hovered && InputHelper::Pressed( VK_LBUTTON ) )
			ctx->FocusedID = GUI::Hash( name );
	}
	else if( ctx->FocusedID == GUI::Hash( name ) ) {
		if( InputHelper::Down( VK_LBUTTON ) ) {
			float offset = std::clamp<float>( Vector2( InputHelper::GetMousePos( ) - DrawPos ).x, 0, DrawSize.x );
			*var_name = GUI::MapNumber( offset, 0, DrawSize.x, min, max );
		}
		else {
			ctx->FocusedID = 0;
		}
	}

	PushCursorPos( CursorPos + Vector2( 0, DrawSize.y + 12 + GUI::ObjectPadding( ) ) );
	return ctx->FocusedID == GUI::Hash( name );
}

bool GUI::Controls::Slider( const std::string& name, int* var_name, int min, int max, const std::string& display, int increment ) {
	Vector2 CursorPos = PopCursorPos( );
	Vector2 DrawPos = ctx->pos + CursorPos;
	Vector2 DrawSize( std::min( ( int )ctx->ParentSize.x - 90, 270 ), 6 );

	DrawPos.x += 20;

	Render::DirectX::Fonts::menu.draw_text( GUI::SplitStr( name, '#' )[ 0 ].data( ), DrawPos + Vector2( 0, -3 ), Color( 203, 203, 203 ), 4 );

	DrawPos.y += 11;

	bool hovered = InputHelper::IsHoveringOverPoint( DrawPos, DrawSize + Vector2( 0, 1 ) ) && InputHelper::IsHoveringOverPoint( ctx->ParentPos, ctx->ParentSize );

	if( hovered && ctx->FocusedID != GUI::Hash( name ) )
		Render::DirectX::gradient_v( DrawPos + 1, DrawSize - 1, { 57, 57, 57 }, { 73, 73, 73 } );
	else
		Render::DirectX::gradient_v( DrawPos + 1, DrawSize - 1, { 52, 52, 52 }, { 68, 68, 68 } );

	int width = GUI::MapNumber( *var_name, min, max, 0, DrawSize.x );
	Render::DirectX::gradient_v( DrawPos + 1, Vector2( width + 1, DrawSize.y ) - 1, g_Vars.menu.menu_color.ToRegularColor( ), g_Vars.menu.menu_color.ToRegularColor( ) * 0.75f );

	Render::DirectX::rect( DrawPos, DrawSize, { 10, 10, 10 } );

	char buf[ 32 ];
	sprintf_s( buf, display.c_str( ), *var_name );

	Vector2 tooltip_size = Render::DirectX::Fonts::menu_bold.measure_size( buf );
	Render::DirectX::Fonts::menu_bold.draw_text( buf, DrawPos + Vector2( width - ( tooltip_size.x / 2 ), DrawSize.y - 6 ), Color( 203, 203, 203 ), 8 );

	if( ctx->FocusedID == 0 ) {
		if( hovered && InputHelper::Pressed( VK_LBUTTON ) )
			ctx->FocusedID = GUI::Hash( name );
	}
	else if( ctx->FocusedID == GUI::Hash( name ) ) {
		if( InputHelper::Down( VK_LBUTTON ) ) {
			int offset = std::floor<int>( std::clamp<int>( Vector2( InputHelper::GetMousePos( ) - DrawPos ).x, 0, DrawSize.x ) );
			*var_name = ( GUI::MapNumber( offset, 0, DrawSize.x, min, max ) );
		}
		else {
			ctx->FocusedID = 0;
		}
	}

	PushCursorPos( CursorPos + Vector2( 0, DrawSize.y + 12 + GUI::ObjectPadding( ) ) );
	return ctx->FocusedID == GUI::Hash( name );
}