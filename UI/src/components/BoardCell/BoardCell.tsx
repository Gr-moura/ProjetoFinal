import "./BoardCell.css";


/**
 * @interface BoardCellProps
 * @brief Propriedades do componente BoardCell.
 * @property {{x: number, y: number}} position Posição da célula no tabuleiro.
 * @property {string} clickedBy Indica qual jogador clicou na célula (ex: "player1", "player2").
 * @property {(position: BoardCellProps["position"]) => void} handleClickedCell Função para manipular o clique na célula.
 */
interface BoardCellProps {
    position:{x:number, y:number};
    clickedBy:string;
    handleClickedCell: (position:BoardCellProps["position"])=>void;
}


/**
 * @brief Componente que representa uma célula do tabuleiro.
 * @param {BoardCellProps} props Propriedades do componente.
 * @return {JSX.Element} Retorna o componente da célula do tabuleiro.
 */
export const BoardCell = ({position, clickedBy,  handleClickedCell}:BoardCellProps) => {
    /**
     * @brief Manipula o clique na célula.
     * @details Se a célula já foi clicada, a função retorna sem fazer nada. Caso contrário, chama a função `handleClickedCell`.
     */
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