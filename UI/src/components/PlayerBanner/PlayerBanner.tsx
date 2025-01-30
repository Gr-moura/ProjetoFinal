import { useState } from "react";
import "./PlayerBanner.css";
import { playerType } from "../../screens/PlayerSelection/PlayerSelection";


/**
 * @interface playerBannerProps
 * @brief Propriedades do componente PlayerBanner.
 * @extends playerType
 * @property {(playerNick: string, playerName: string) => void} handleSelectPlayer Função chamada ao selecionar um jogador.
 * @property {string} [playerType] Tipos para customização adicional do banner (ex: "new" para banner de criar jogador, "nameless" para jogador sem nome).
 */
interface playerBannerProps extends playerType{
    handleSelectPlayer:(playerNick:string, playerName:string)=>void;
    playerType?:string;
}


/**
 * @brief Componente que representa um banner de jogador.
 * @param {playerBannerProps} props Propriedades do componente.
 * @return {JSX.Element} Retorna o componente do banner do jogador.
 */
export const PlayerBanner = ({playerNick, playerName, score, handleSelectPlayer, playerType}:playerBannerProps) => {
    const [newPlayerName, setNewPlayerName] = useState("");
    const [newPlayerNickname, setNewPlayerNickname] = useState("");
    const [highlighted, setHighlighted] = useState(false);

    const [hide, setHide] = useState(false);

    /**
     * @brief Manipula o clique no banner.
     * @details Se o jogador for do tipo "new" e não estiver destacado, destaca o banner. Caso contrário, chama a função `handleSelectPlayer`.
     */
    const handleClick = () => {
        if(playerType==="new" && !highlighted){
            setHighlighted(true);
        }
        else if(playerType!="new"){
            handleSelectPlayer(playerNick, playerName);
        }
    }

    /**
     * @brief Cria um novo jogador.
     * @details Chama a função `handleSelectPlayer` com os dados do novo jogador e remove o destaque do banner.
     */
    const handleCreateNewPlayer = () => {
        setHighlighted(false);
        handleSelectPlayer(newPlayerNickname, newPlayerName);
    }

    /**
     * @brief Remove um jogador da lista.
     * @details Filtra o jogador da lista salva no localStorage e recarrega a página.
     * @return {boolean} Retorna `true` se o jogador foi removido com sucesso, caso contrário `false`.
     */
    const handleDeletePlayer = () => {
        let players = localStorage.getItem("players");
        if(players && playerType!="new"){
            players = JSON.parse(players);
            // @ts-ignore
            players = players.filter((player)=>(player.playerNick!=playerNick));
            localStorage.setItem("players", JSON.stringify(players));
            window.location.reload();
            setHide(true);
            return true;
        }
        return false;
    }

    return (
        <div className="playerbannerouterbody">
            {!hide && (<button className={"deletebutton"+(playerType==="new"||playerType==="nameless"?" hideopacity":"")} onClick={()=>handleDeletePlayer()}>🗑</button>)}
            {!hide && (<div className={"playerbannerbody"+(highlighted?" playerbannerhighlighted":"")} onClick={()=>handleClick()}>
                <h3 className={"playernickname"+(highlighted?" playerbannerhighlighted":"")}>{playerNick}</h3>
                <div className="borderdiv"></div>
                <div>
                    {playerType!="new" && playerType!="nameless" && (<a className="playername">Nome: {playerName}</a>)}
                </div>
                {score && (<ul style={{marginTop:"20px"}}>
                    {score.map((item)=>(
                        <li key={item.gameName} style={{display:"flex", flexDirection:"column", marginBottom:"10px"}}>
                            <a>Jogo: {item.gameName}</a>
                            <a>Vitórias: {item.wins.toString()}</a>
                            <a>Empates: {item.ties.toString()}</a>
                            <a>Derrotas: {item.losses.toString()}</a>
                        </li>
                    ))}
                </ul>)}
                {playerType==="new" &&(
                    <div>
                        <div style={{position:"relative"}} className={highlighted?"playerbannerhighlighted":"hidden"}>
                            <div style={{marginTop:"10px"}}>
                                <a>Digite o seu nome: </a>
                                <input className="newplayerinput" name="playername" 
                                    onChange={(event)=>setNewPlayerName(event.target.value)}
                                />
                            </div>
                            <div style={{marginTop:"10px"}}>
                                <a>Digite o seu apelido: </a>
                                <input className="newplayerinput" name="playername" 
                                    onChange={(event)=>setNewPlayerNickname(event.target.value)}
                                />
                            </div>
                            <div style={{marginTop:"100px",display:"flex", "alignItems":"center", "justifyContent":"center"}}>
                                <button className="createnewplayerbutton" onClick={()=>handleCreateNewPlayer()}>Criar</button>
                            </div>
                        </div>
                        <div style={{position:"relative", display:"flex", alignItems:"center", justifyContent:"center"}} className={highlighted?"hidden":""}>
                            <a className="createplayerplus">+</a>
                        </div>
                    </div>
                )}
            </div>)}
        </div>
    )
}