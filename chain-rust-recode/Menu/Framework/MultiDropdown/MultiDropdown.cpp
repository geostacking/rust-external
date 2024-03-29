#include "../gui.h"
#include <algorithm>
#include "../../../stdafx.hpp"

void _line( Vector2 pos, bool nigger = false ) {
	for( auto i = 5; i >= 2; --i ) {
		auto offset = 5 - i;
		Render::DirectX::line( Vector2( pos.x + offset, pos.y + offset ), Vector2( pos.x + offset + std::clamp( i - offset, 0, 5 ), pos.y + offset ), nigger ? Color( 0, 0, 0 ) : Color( 151, 151, 151 ) );
	}
}

bool GUI::Controls::MultiDropdown( const std::string& name, std::vector< MultiItem_t > options, int max_items ) {
	Vector2 CursorPos = PopCursorPos( );
	Vector2 DrawPos = ctx->pos + CursorPos;
	Vector2 DrawSize = Vector2( std::min( ( int )ctx->ParentSize.x - 90, 270 ), 19 );

	DrawPos.x += 20;

	Render::DirectX::Fonts::menu.draw_text( GUI::SplitStr( name, '#' )[ 0 ].data( ), DrawPos + Vector2( 1, -3 ), Color( 203, 203, 203 ), 4 );

	DrawPos.y += 11;

	bool hovered = InputHelper::IsHoveringOverPoint( DrawPos, DrawSize ) && InputHelper::IsHoveringOverPoint( ctx->ParentPos, ctx->ParentSize );

	if( hovered || ctx->MultiDropdownInfo.HashedID == GUI::Hash( name ) )
		Render::DirectX::gradient_v( DrawPos, DrawSize, { 41, 41, 41 }, { 46, 46, 46 } );
	else
		Render::DirectX::gradient_v( DrawPos, DrawSize, { 31, 31, 31 }, { 36, 36, 36 } );

	_line( DrawPos + DrawSize - Vector2( 9, 6 ) - Vector2( 0, 6 ), true );
	_line( DrawPos + DrawSize - Vector2( 9, 6 ) + Vector2( 0, 1 ) - Vector2( 0, 6 ) );

	bool too_long = false;
	char buf[ 128 ] = { 0 };
	for( int i = 0; i < options.size( ); i++ ) {
		auto& it = options.at( i ).value;

		if( !*it )
			continue;

		strcat( buf, options.at( i ).name.data( ) );

		if( i != options.size( ) - 1 )
			strcat( buf, ( ", " ) );

		auto max_text_width = DrawSize.x - ( 25 + Render::DirectX::Fonts::menu.measure_size( _ ( "..." ) ).x );
		if( Render::DirectX::Fonts::menu.measure_size( buf ).x > max_text_width ) {
			// remove last character until string width is okay
			if( max_text_width >= 1 ) {
				while( Render::DirectX::Fonts::menu.measure_size( buf ).x > max_text_width || buf[ strlen( buf ) - 1 ] == ',' || buf[ strlen( buf ) - 1 ] == ' ' ) {
					buf[ strlen( buf ) - 1 ] = '\0';
				}
			}

			too_long = true;
			break;
		}
	}

	if( too_long )
		strcat( buf, _ ( "..." ) );

	if( strlen( buf ) == 0 )
		strcat( buf, _ ( "-" ) );

	if( buf[ strlen( buf ) - 1 ] == ' ' )
		buf[ strlen( buf ) - 2 ] = '\0';

	if( buf[ strlen( buf ) - 1 ] == ' ' )
		buf[ strlen( buf ) - 2 ] = '\0';


	Render::DirectX::rect( DrawPos, DrawSize, { 10, 10, 10 } );
	Render::DirectX::Fonts::menu.draw_text( buf, DrawPos + Vector2( 10, 4 ), { 150, 150, 150 }, 0 );

	if( ctx->FocusedID == 0 ) {
		if( hovered && InputHelper::Pressed( VK_LBUTTON ) )
			ctx->FocusedID = GUI::Hash( name );
	}
	else if( ctx->FocusedID == GUI::Hash( name ) ) {
		if( hovered ) {
			ctx->MultiDropdownInfo.Elements = options;
			ctx->MultiDropdownInfo.Size = DrawSize.x;
			ctx->MultiDropdownInfo.Pos = DrawPos + Vector2( 0, DrawSize.y + 3 );
			ctx->MultiDropdownInfo.HashedID = GUI::Hash( name );
		}
	}

	GUI::PushCursorPos( CursorPos + Vector2( 0, DrawSize.y + GUI::ObjectPadding( ) + 12 ) );
	return true;
}
