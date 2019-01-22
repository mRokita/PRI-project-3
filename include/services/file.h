/*
 * This file is part of the PRI-project-3 distribution (https://github.com/mRokita/PRI-project-3.
 * Copyright (c) 2018 Michał Rokita.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PRI3_FILE_H
#define PRI3_FILE_H
#include "../../include/services/file.h"
#include "../../include/data/animal.h"

void
load_data_from_file(AnimalLinkedList* list);

void
save_data_to_file(AnimalLinkedList* animals);

#endif //PRI3_FILE_H
