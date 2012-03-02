# $Id: openttd.desktop.translation.awk 19884 2010-05-22 19:59:37Z rubidium $

# This file is part of OpenCoaster Tycoon.
# OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
# OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.

#
# Awk script to automatically generate a single comment line
# for a translated desktop shortcut. If it does not exist there
# is no output.
#

/##isocode/ { lang = $2; next }
/STR_DESKTOP_SHORTCUT_COMMENT/ { sub("^[^:]*:", "", $0); print "Comment[" lang "]=" $0; next}
