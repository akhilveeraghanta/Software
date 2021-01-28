import re

ALLOWED_ACRONYMS = [
   "ai",
   "ssl",
   "id",
]

def to_pascal_case(snake_str):
    return "".join(x.upper() if x in ALLOWED_ACRONYMS else x.title() for x in snake_str.split("_"))


def to_camel_case(snake_str):
    pascal_case = to_pascal_case(snake_str)
    return pascal_case[0].lower() + pascal_case[1:]


def to_snake_case(camel_str):
    return re.sub(r"(?<!^)(?=[A-Z])", "_", camel_str).lower()
