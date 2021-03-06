/*Copyright Vincent Lanore 2017-2018

  This file is part of Menhyr.

  Menhyr is free software: you can redistribute it and/or modify it under the terms of the GNU
  Lesser General Public License as published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  Menhyr is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
  General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with Menhyr. If
  not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "HexCoords.hpp"
#include "TileData.hpp"
#include "globals.hpp"

/*
====================================================================================================
  ~*~ TileMap ~*~
==================================================================================================*/
class TileMap : public GameObject {
    sf::Texture tileset;
    sf::VertexArray array;
    int w{144};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        states.texture = &tileset;
        target.draw(array, states);
    }

  public:
    TileMap(string tileset_name = "png/alltiles.png") {
        tileset.loadFromFile(tileset_name);
        array.setPrimitiveType(sf::Quads);
    }

    void load(const std::unordered_map<HexCoords, TileData>& grid) {
        array.resize(grid.size() * 4);

        auto it = grid.begin();  // needs iteration with index
        int i = 0;
        while (it != grid.end()) {
            auto hex_coords = it->first;
            auto tile_type = it->second;

            sf::Vertex* quad = &array[i * 4];
            vec tile_dim{258, 193};
            vec tile_center{109, 88};
            vec hex_center = hex_coords.get_pixel(w);
            vec tl = hex_center - tile_center;
            vec br = tl + tile_dim;
            vec tex_tl = vec{0, tile_type.first * tile_dim.y};
            quad[0].position = tl;
            quad[1].position = vec{br.x, tl.y};
            quad[2].position = br;
            quad[3].position = vec{tl.x, br.y};
            quad[0].texCoords = tex_tl;
            quad[1].texCoords = tex_tl + vec{tile_dim.x, 0};
            quad[2].texCoords = tex_tl + tile_dim;
            quad[3].texCoords = tex_tl + vec{0, tile_dim.y};
            if (tile_type.second == 0) {
                quad[0].color = sf::Color(255, 230, 230);
                quad[1].color = sf::Color(255, 230, 230);
                quad[2].color = sf::Color(255, 230, 230);
                quad[3].color = sf::Color(255, 230, 230);
            } else {
                quad[0].color = sf::Color::White;
                quad[1].color = sf::Color::White;
                quad[2].color = sf::Color::White;
                quad[3].color = sf::Color::White;
            }
            it++;
            i++;
        }
    }
};
