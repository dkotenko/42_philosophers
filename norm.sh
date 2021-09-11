# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colorised_norm.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/25 18:53:10 by ggerardy          #+#    #+#              #
#    Updated: 2021/04/09 22:19:25 by amalliar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
​
#!/usr/bin/env bash
​
# Write here color codes you want
## You can find codes here: http://www.lihaoyi.com/post/Ansi/Rainbow256.png
### Warning! In your terminal colors may differ
​
# ! better way to change colors:
#	use installer:
# sh -c "$(curl -s https://bitbucket.org/liftchampion/colorised-norminette/raw/b4272f2c2dac52b1da721ae658815c43f64e5cb2/colorised_norm_install_installer.sh)"
NORM_COLOR=29
NO_NORM_COLOR=202
​
python3 -m norminette $* | awk -v nc="$NORM_COLOR" -v nnc="$NO_NORM_COLOR" '
BEGIN {}
{
    buf = $0
    if ($2 == "OK!") { print "\x1B[38;5;" nc "m" buf "\x1B[0m" }
    else if ($2 == "Error!") { print "\x1B[38;5;" nnc "m" buf "\x1B[0m" }
    else { print buf }
}
'