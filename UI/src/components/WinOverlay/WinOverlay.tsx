import { Link } from "react-router-dom";
import "./WinOverlay.css";

interface WinOverlayProps{
    winnerplayer:string;
    wintype:string;
    reset: (arg0:boolean)=>void;
    className?:string;
}

export const WinOverlay = ({winnerplayer, wintype, reset, className}:WinOverlayProps) => {
    //handles a request to play the game again
    const handleRetryRequest = () => {
        reset(true);
    }

    return (
        <div className={"winoverlaybody "+className}>
            <button className="retrybutton" onClick={()=>handleRetryRequest()}>
                <h1 className="retrytext">{"Jogar novamente >"}</h1>
            </button>
            <Link to={"/"}>
                <button className="menubutton">
                    <h1 className="menutext">{"< Selecionar jogadores"}</h1>
                </button>
            </Link>
            <h2>{wintype==="tie"? "Empate!" : ("Parabéns! Jogador " + winnerplayer + " venceu!")}</h2>
        </div>
    )
}