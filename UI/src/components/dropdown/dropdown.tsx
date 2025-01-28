import "./dropdown.css"
import { useEffect, useState } from "react";
import { FaChevronDown, FaChevronUp } from "react-icons/fa";


interface SingleLevelDropdownMenuProps {
  buttonLabel: string;
  items: {
    title: string;
    url?: string;
    icon?: JSX.Element;
    action?: () => void;
  }[];
}


export const SingleLevelDropdownMenu = ({buttonLabel, items}: SingleLevelDropdownMenuProps) => {
  const [open, setOpen] = useState(false);
  const handleToggle = () => {
    setOpen((prev) => !prev);
  };

  const [button_tittle, setButtonTittle] = useState("");
  useEffect(()=>{
    setButtonTittle(buttonLabel);
  }, []);

  return (
    <div className="dropdownbody">    
      <button className="dropdownbutton" type="button" onClick={handleToggle}>
        {button_tittle}
        {open ? <FaChevronUp /> : <FaChevronDown />}
      </button>
      {open && (
        <div className="dropdownitems">
          <ul className="dropdownitemslist">
            {items.map((item, index) => (
            <li className="dropdownitem" key={index}>
                <button className="dropdownitembutton" onClick={()=>{item.action?.(); setButtonTittle(item.title); setOpen(false)}}>
                    {item.title}
                </button>
              </li>))}
          </ul>
        </div>)}
    </div>
  );
};