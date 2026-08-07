#include "../import/CommandExecutor.h"

using Type = CommandExecutor::CommandType;

const std::vector<std::pair<std::string, Type>> CommandExecutor::cmd{
  {"--help", Type::Help},
  {"--clear", Type::Clear},
  {"--exit", Type::Exit},

  {"--export ", Type::Export},
  {"--import ", Type::Import},
  {"--history", Type::History},

  {"--precision ", Type::Precision},

  {"--reset-prop", Type::ResetProperties},
  {"--free-all", Type::FreeAll},

  {"--func-list", Type::FuncList},
  {"--const-list", Type::ConstList},
  {"--vars-list", Type::VarsList},
  {"--prop-list", Type::PropList},
  {"--std-list", Type::StdList},
};

const std::string CommandExecutor::help_msg = {
  "Консольное приложение, позволяющее выполнять инженерные и математические вычисления "
   "с высокой точностью. Программа поддерживает ввод математических выражений, основные "
   "арифметические операции, математические функции и обработку ошибок.\n"
   "\n\n"
   "--help          справка о возможностях\n"
   "--clear         очистка терминала\n"
   "--exit          завершение работы\n"
   "\n"
   "--export .math  экспорт сущностей\n"
   "--import .math  импорт сущностей\n"
   "--history       история вычислений\n"
   "\n"
   "--precision 9   установка количества знаков в десятичных дробях при выводе\n"
   "\n"
   "--reset-prop    сброс всех глобальных и локальных свойств\n"
   "--free-all      удаление всех объявленных функций, констант и переменных\n"
   "\n"
   "--func-list     список объявленных функций\n"
   "--const-list    список объявленных констант\n"
   "--var-list      список объявленных переменных\n"
   "--prop-list     список всех глобальных и локальных свойств\n"
   "\n"
   "--std-list      список всех стандартных констант и функций"
};

CommandExecutor::CommandExecutor(std::ostream& os, GlobalContext& context, Settings& settings) :
  os_(os), context_(context), settings_(settings) {
}

Type CommandExecutor::Execute(const std::string& input) {
  auto iter = std::find_if(cmd.begin(), cmd.end(), [&input](const std::pair<std::string, Type>& el) {
    return input.starts_with(el.first);
  });
  if (iter == cmd.end()) {
    throw std::runtime_error("Неизвестная команда");
  }

  Type command = iter->second;
  switch (command) {
    case CommandType::Help:
      os_ << help_msg << "\n\n";
      break;
    case CommandType::Clear:
      os_ << "\x1b[2J\x1b[3J\x1b[H";
      break;
    case CommandType::Exit:
      os_ << "Завершение работы";
      break;
    
    case CommandType::Export:
      #warning "Дописать код"
      break;
    case CommandType::Import:
      #warning "Дописать код"
      break;
    case CommandType::History:
      #warning "Дописать код"
      break;
    
    case CommandType::Precision:
      {
        std::string_view arg = input;
        arg.remove_prefix(iter->first.length());
        int value = 0;
        auto res = std::from_chars(arg.data(), arg.data() + arg.size(), value);
        if (res.ec != std::errc()) {
          throw std::runtime_error("--precision ... ожидает целочисленное значение");
        }
        settings_.precision = value;
        os_ << "Точность: " << value << " знаков в десятичных дробях\n\n";
      }
      break;

    case CommandType::ResetProperties:
      context_.ResetProperties();
      os_ << "Сброс значений атрибутов\n\n";
      break;
    case CommandType::FreeAll:
      context_.FreeAll();
      os_ << "Удаление всех констант, функций и переменных\n\n";
      break;

    case CommandType::FuncList:
      #warning "Дописать код"
      break;
    case CommandType::ConstList:
      #warning "Дописать код"
      break;
    case CommandType::VarsList:
      #warning "Дописать код"
      break;
    case CommandType::PropList:
      #warning "Дописать код"
      break;
    case CommandType::StdList:
      #warning "Дописать код"
      break;
  }

  return command;
}