��    N      �  k   �      �  o   �  ?     �   Y  .   �  #        C  '   ^     �     �     �     �  (   �     �  K   	     ^	     c	  -   k	     �	     �	     �	  R   �	     
     
  8   1
  M   j
  k   �
  8   $  (   ]     �  �   �     f  u   �     �        X     @   ^     �     �  ;   �       6   )  7   `  �   �  /   !  4   Q  =   �  Y   �  �    )   �  7        D  1   c  '   �  .   �  C   �    0     N  �   g  \   �     F     L     R     X     ^  n   ~     �  @        G  &   d     �     �  '   �     �  !   �       a        �  �  �  �   G  n   "  �   �  t   �  N     Q   S  m   �       8   -  '   f     �  S   �  [   �  �   [  
   �     �  ^   	     h     �     �  �   �     t   %   �   V   �   �   !  �   �!  �   |"  ?   #     G#  �  Z#  K   %  �   _%  
   V&  
   a&  �   l&  m   '     �'  E   �'  k   �'  U   _(  �   �(  H   6)  �   )  \   h*  Z   �*  L    +  �   m+  �  ,  i   �/  O    0  =   P0  S   �0  \   �0  Q   ?1  h   �1  Y  �1  >   T4    �4  �   �5     ]6     i6     }6     �6  9   �6  �   �6  Y   y7  o   �7  8   C8  v   |8     �8  4   �8  O   /9  .   9  K   �9  9   �9  �   4:     ;     K   @             &          3                  E   '   "       ,       (   >                    -   9                                   /            C   	          H                    G   D   *                  =       L       ;      $   .       B      0   N   2      )   <   ?   A   
   7      6   M   4       5      +       1   I   !   :   %               F       #         8             J    
        --outdated		Merge in even outdated translations.
	--drop-old-templates	Drop entire outdated templates. 
  -o,  --owner=package		Set the package that owns the command.   -f,  --frontend		Specify debconf frontend to use.
  -p,  --priority		Specify minimum priority question to show.
       --terse			Enable terse mode.
 %s failed to preconfigure, with exit status %s %s is broken or not fully installed %s is fuzzy at byte %s: %s %s is fuzzy at byte %s: %s; dropping it %s is missing %s is missing; dropping %s %s is not installed %s is outdated %s is outdated; dropping whole template! %s must be run as root (Enter zero or more items separated by a comma followed by a space (', ').) Back Choices Config database not specified in config file. Configuring %s Continue Debconf Debconf is not confident this error message was displayed, so it mailed it to you. Debconf on %s Debconf, running at %s Dialog frontend is incompatible with emacs shell buffers Dialog frontend requires a screen at least 13 lines tall and 31 columns wide. Dialog frontend will not work on a dumb terminal, an emacs shell buffer, or without a controlling terminal. Enter the items you want to select, separated by spaces. Extracting templates from packages: %d%% Help If you quit this configuration dialog, then the package being configured will probably fail to install, and you may have to fix it manually. This may be especially difficult if you are in the middle of a large upgrade. Ignoring invalid priority "%s" Input value, "%s" not found in C choices! This should never happen. Perhaps the templates were incorrectly localized. More Next No usable dialog-like program is installed, so the dialog based frontend cannot be used. Note: Debconf is running in web mode. Go to http://localhost:%i/ Package configuration Preconfiguring packages ...
 Problem setting up the database defined by stanza %s of %s. Really quit configuration? TERM is not set, so the dialog frontend is not usable. Template #%s in %s does not contain a 'Template:' line
 Template #%s in %s has a duplicate field "%s" with new value "%s". Probably two templates are not properly separated by a lone newline.
 Template database not specified in config file. Template parse error near `%s', in stanza #%s of %s
 Term::ReadLine::GNU is incompatable with emacs shell buffers. The Sigils and Smileys options in the config file are no longer used. Please remove them. The editor-based debconf frontend presents you with one or more text files to edit. This is one such text file. If you are familiar with standard unix configuration files, this file will look familiar to you -- it contains comments interspersed with configuration items. Edit the file, changing any items as necessary, and then save it and exit. At that point, debconf will read the edited file, and use the values you entered to configure the system. This frontend requires a controlling tty. Unable to load Debconf::Element::%s. Failed because: %s Unable to start a frontend: %s Unknown template field '%s', in stanza #%s of %s
 Usage: debconf [options] command [args] Usage: debconf-communicate [options] [package] Usage: debconf-mergetemplate [options] [templates.ll ...] templates Usage: dpkg-reconfigure [options] packages
  -u,  --unseen-only		Show only not yet seen questions.
       --default-priority	Use default priority instead of low.
       --force			Force reconfiguration of broken packages.
       --no-reload		Do not reload templates. (Use with caution.) Valid priorities are: %s You are using the editor-based debconf frontend to configure your system. See the end of this document for detailed instructions. You may need to quit anyway if you are stuck in a configuration loop due to a buggy package. _Back _Help _Next _Quit apt-extracttemplates failed: %s debconf-mergetemplate: This utility is deprecated. You should switch to using po-debconf's po2debconf program. debconf: can't chmod: %s delaying package configuration, since apt-utils is not installed falling back to frontend: %s must specify some debs to preconfigure no none of the above please specify a package to reconfigure template parse error: %s unable to initialize frontend: %s unable to re-open stdin: %s warning: possible database corruption. Will attempt to repair by adding back missing question %s. yes Project-Id-Version: 1.5.66
Report-Msgid-Bugs-To: 
PO-Revision-Date: 2018-04-29 08:45+0300
Last-Translator: Yuri Kozlov <yuray@komyakino.ru>
Language-Team: Russian <debian-l10n-russian@lists.debian.org>
Language: ru
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: Lokalize 2.0
Plural-Forms:  nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
 
        --outdated		Выполнять объединение даже с устаревшими переводами.
	--drop-old-templates	Выкидывать устаревшие шаблоны полностью. 
  -o,  --owner=пакет		Указать пакет, которому принадлежит команда.   -f,  --frontend		Задать желаемый интерфейс debconf.
  -p,  --priority		Указать желаемый приоритет задаваемых вопросов.
       --terse			Включить лаконичный режим.
 не удалось выполнить начальную настройку пакета %s, код ошибки %s Пакет %s сломан или установлен не полностью %s имеет нечёткий перевод начиная с %s байта: %s %s имеет нечёткий перевод начиная с %s байта: %s; отбрасывается отсутствует %s отсутствует %s; отбрасывается %s Пакет %s не установлен Пакет %s устарел Пакет %s устарел; игнорирование всего шаблона! %s требует выполнения с правами суперпользователя (Укажите необходимое количество элементов, разделяя их запятой с пробелом (', ').) Назад Варианты База данных настройки не указана в файле настройки. Настраивается %s Продолжить Debconf По данным debconf непонятно, выводилось ли это сообщение об ошибке на экран, поэтому оно было вам отправлено по почте. Debconf на %s Debconf, работающий на %s Интерфейс dialog не совместим с буферами shell из emacs Для интерфейса dialog требуется экран не менее 13 строк в высоту и 31 колонки в ширину. Интерфейс dialog не будет работать на неуправляемом (dumb) терминале, из буфера emacs shell или в отсутствие контролирующего терминала. Укажите буквы, соответствующие выбранным вариантам, разделяя их пробелами. Извлекаются шаблоны из пакетов: %d%% Подсказка Если вы прервёте настройку, то настраиваемый пакет, вероятно, не будет установлен из-за ошибки, и вам может потребоваться исправлять её вручную. Это может оказаться особенно трудно, если вы находитесь в середине большого обновления системы. Неправильный приоритет «%s» игнорируется Входное значение «%s» не найдено среди вариантов локали С! Это не должно было случиться. Возможно, шаблоны были неправильно переведены. Далее Далее Ни одна из dialog-подобных программ не установлена, поэтому вы не можете использовать dialog-интерфейс. Замечание: используется веб-интерфейс. Откройте http://localhost:%i/ Настройка пакета Предварительная настройка пакетов …
 Проблемы при настройке базы данных, заданной строкой %s в %s. Вы действительно хотите прекратить настройку? Не установлена переменная TERM, поэтому запустить интерфейс dialog нельзя. Шаблон #%s в %s не содержит строки «Template:»
 Шаблон #%s в %s содержит повторяющееся поле «%s» с другим значением «%s». Вероятно, два шаблона не разделены символом новой строки.
 База данных шаблонов не указана в файле настройки. Ошибка разбора шаблона около «%s», в строке #%s из %s
 Term::ReadLine::GNU не совместим с буферами emacs shell. Параметры Sigils и Smileys в файле настройки устарели и больше не используются. Удалите их. Интерфейс к debconf, использующий текстовый редактор, предлагает вам редактировать один или несколько текстовых файлов. Перед вами один из таких файлов. Его формат схож с форматом стандартных файлов настройки Unix: параметры и их значения идут вперемешку с описывающими их комментариями. Вы должны изменить этот файл в соответствии с вашими потребностями, сохранить его и выйти из редактора. Затем программа debconf прочитает изменённый файл и использует введённые вами параметры для настройки системы. Этот интерфейс работает только с управляющего терминала. Не удалось загрузить Debconf::Element::%s. Причина: %s Не удалось запустить интерфейс: %s Неизвестное поле шаблона «%s», в строке #%s из %s
 Использование: debconf [параметры] команда [аргументы] Использование: debconf-communicate [параметры] [пакет] Использование: debconf-mergetemplate [параметры] [templates.ll …] шаблоны Использование: dpkg-reconfigure [параметры] пакеты
  -u,  --unseen-only		Показывать только ещё не просмотренные вопросы.
       --default-priority	Использовать приоритет по умолчанию
                         	вместо низкого.
       --force			Принудительная перенастройка сломанных
              			пакетов.
       --no-reload		Не перезагружать шаблоны
                         	(используйте осторожно). Возможные значения приоритетов: %s Вы указали пакету debconf, что для настройки системы необходимо использовать текстовый редактор. Подробную информацию вы найдёте в конце этого документа. Но иногда всё же требуется завершение, если вы застряли в кольце настроек из-за дефектного пакета. _Назад _Подсказка _Далее _Выйти ошибка при работе apt-extracttemplates: %s debconf-mergetemplate: Эта программа устарела. Используйте вместо неё программу po2debconf из пакета po-debconf. debconf: не удалось изменить режим доступа к файлу: %s так как не установлен apt-utils, настройка пакетов откладывается будет использован интерфейс: %s для предварительной настройки нужно указать несколько deb-файлов нет ни один из предложенных выше укажите пакет, который нужно перенастроить ошибка разбора шаблона: %s не удалось инициализировать интерфейс: %s не удалось заново открыть stdin: %s внимание: возможно, повреждена база данных. Будет сделана попытка исправить её, добавив отсутствующий вопрос %s. да 