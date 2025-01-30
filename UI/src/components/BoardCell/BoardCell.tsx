import "./BoardCell.css";

interface BoardCellProps {
    position:{x:number, y:number};
    clickedBy:string;
    handleClickedCell: (position:BoardCellProps["position"])=>void;
}
export const BoardCell = ({position, clickedBy,  handleClickedCell}:BoardCellProps) => {
    const handleClick = () => {
        if(clickedBy) return;
        handleClickedCell(position);
    }

    return(
        <div>
            <div className={"cell" + (clickedBy? (" flip "+clickedBy) : "")} onClick={()=>handleClick()}></div>
        </div>
    )
}